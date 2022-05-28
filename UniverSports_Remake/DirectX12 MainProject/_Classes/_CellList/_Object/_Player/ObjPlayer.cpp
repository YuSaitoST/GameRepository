#include "ObjPlayer.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_UI/_CharaIcon/IconAnimator.h"
#include "_Classes/_CellList/_BallsInstructor/BallsInstructor.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_FileNames/FileNames.h"
#include "DontDestroyOnLoad.h"

ObjPlayer::ObjPlayer() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, NONE_COLLI_TYPE, Vector3::Zero, 0.0f);

	physics_		= new btObject(NONE_BULLET_TYPE, Vector3::Zero, Vector3::Zero, 0.0f, 0.0f);
	life_			= nullptr;
	teamID_			= nullptr;
	ti_respone_		= nullptr;
	eff_down_		= nullptr;
	strategy_		= nullptr;
	barrier_		= nullptr;
	myBallID_		= -1;
	hasBall_		= false;
	isDown_			= false;
}

ObjPlayer::ObjPlayer(OPERATE_TYPE strategy, Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(PLAYER, COLLI_TYPE::SPHRER, pos, r);

	physics_		= new btObject(BULLET_TYPE::BT_SPHRER, pos, Vector3::Zero, 0.0f, 1.0f);
	rotate_			= Vector2(0.0f, GAME_CONST.Player_FacingRight);
	myBallID_		= -1;
	hasBall_		= false;
	isDown_			= false;

	life_			= std::make_unique<MyLife>(3);
	teamID_			= std::make_unique<TeamID>();
	ti_respone_		= std::make_unique<CountTimer>(PLAYER_PARAM.TIME_RESPONE);
	eff_down_		= std::make_unique<EffDown>();
	barrier_		= std::make_unique<Barrier>();
	
	strategy_		=	(strategy == OPERATE_TYPE::MANUAL)	 ? static_cast<CharaStrategy*>(new ManualChara())   : 
						(strategy == OPERATE_TYPE::COMPUTER) ? static_cast<CharaStrategy*>(new ComputerChara()) : nullptr;
}

ObjPlayer::~ObjPlayer() {
	if (strategy_ != nullptr)
		delete strategy_;

	//delete barrier_;
	//delete eff_down_;
	//delete ti_respone_;
	//delete teamID_;
	//delete life_;
	delete physics_;
}

void ObjPlayer::Initialize(const int id) {
	strategy_->Initialize(id, this);
	eff_down_->Initialize("Down" + std::to_string(id));
	physics_->SetActivationState(DISABLE_DEACTIVATION);

	id_my_ = id;

	if (DontDestroy->GameMode_.isSINGLES_GAME()) {
		DontDestroy->TeamID[id_my_] = id_my_;
	}

	teamID_->Set(DontDestroy->TeamID[id_my_]);
}

void ObjPlayer::LoadAssets(std::wstring file_name) {
	strategy_->LoadAssets();
	eff_down_->LoadAsset(L"_Effects\\_Down\\HITeffect.efk");

	CreateModel(file_name);
	rotate_		= Vector2(strategy_->GetRotateX(), GAME_CONST.Player_FacingRight);
	forward_ = Vector2(std::cosf(rotate_.x), std::sinf(rotate_.x));
	r_			= model_->GetBoundingSphere().Radius;
	
	barrier_->LoadAsset(r_);
	collision_->SetColli(model_->GetBoundingSphere());
	collision_->SetColliScale(1.2f);

	AssignPosition();

	SetTransforms(pos_, rotate_);
	UpdateToMorton();
}

void ObjPlayer::Update(const float deltaTime) {
	if (life_->NowLifePoint() <= 0)
		return;

	if (isDown_)
		Beaten(deltaTime);
	else
		Playing(deltaTime);
}

void ObjPlayer::Render() {
	if (life_->NowLifePoint() <= 0)
		return;

	model_->Draw();
}

void ObjPlayer::UIRender() {
	if (life_->NowLifePoint() <= 0)
		return;

	strategy_->UIRender();
}

void ObjPlayer::AlphaRender() {
	barrier_->Render();
}

/**
* @brief 衝突時の処理
* @param hitObject 衝突した物体
*/
void ObjPlayer::HitAction(ObjectBase* hitObject) {
	// 衝突したものがないなら早期リターン
	if (hitObject == nullptr)
		return;

	const OBJ_TYPE _type = hitObject->myObjectType();

	// タイプ別の衝突判定
	if (_type == BALL) {
		ObjBall* _ball = dynamic_cast<ObjBall*>(hitObject);  // ボールの状態を知るためにダウンキャスト

		if (id_my_ == _ball->GetOwnerID())  // 自分が持つボールとの当たり判定は取る必要なし
			return;

		const B_STATE _baleState = _ball->NowState();

		if (_baleState == B_STATE::FLOATING) {  // キャッチ処理
			// ボールを持っている且つ保持ボールのIDが存在する
			if (hasBall_ && myBallID_ != -1)
				return;

			CautchedBall(_ball->myObjectID());
		}
		else if (_baleState == B_STATE::SHOT) {  // やられ処理

			// バリアが出ているなら
			if (barrier_->IsDisplayed())
				return;

			// 同じチームのメンバーが投げたボールはヒットしない
			if (teamID_->Get(_ball->GetOwnerID()) == teamID_->Get())
				return;

			eff_down_->PlayOneShot();
			eff_down_->Set_Position(Vector3(pos_.x, pos_.y, 0.0f));

			// 当たり判定を消すために、一旦明らかに場外な位置へ移動させる
			SetTransforms(Vector2(99.0f, 99.0f), rotate_);
			pos_ = Vector2(GAME_CONST.S_POS[id_my_].x, GAME_CONST.S_POS[id_my_].y);

			isDown_ = true;

			// ゴールを用いるモードではライフの処理はない
			if (!DontDestroy->GameMode_.isGAMES_WITH_GOALS()) {
				IconAnimator::DisplayOn();
				life_->TakeDamage();
				ResetVelocity();
				if (life_->NowLifePoint() <= 0)
					DontDestroy->Survivor_[id_my_] = false;
			}

			instructor_->BreakOfThrower(_ball->myObjectID());

			if (hasBall_) {
				instructor_->BreakOfTheHitter(myBallID_);
				myBallID_ = -1;
				hasBall_ = false;
			}
		}
	}
}

/**
* @brief 座標と回転をセットする
* @param pos 座標
* @param rotate 回転
*/
void ObjPlayer::SetTransforms(XMFLOAT2 pos, XMFLOAT2 rotate) {
	model_->SetPosition(Vector3(pos.x, pos.y, 0.0f));
	model_->SetRotation(Vector3(rotate.x, rotate.y, 0.0f));
	barrier_->SetPosition(Vector3(pos.x, pos.y, 0.0f));
	SetTransform(XMFLOAT3(pos.x, pos.y, 0.0f), rotate);
}

/**
* @brief モデル生成
* @param fileName ファイル名
*/
void ObjPlayer::CreateModel(std::wstring fileName) {
	model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, fileName.c_str());
	model_->SetScale(PLAYER_PARAM.SCALE);
	model_->SetMaterial(GetNomMaterial());
}

/**
* @brief アニメーションをリセットする
*/
void ObjPlayer::AnimReset() {
	const int _limit = (int)(6 * 0.5f);
	for (int _i = 0; _i <= _limit; _i += 3) {
		model_->SetTrackEnable(_i, false);
		model_->SetTrackEnable(_i + 1, false);
		model_->SetTrackEnable(_i + 2, false);
	}
}

/**
* @brief アニメーションをセットする
* @param motion アニメーション
* @param deltaTime フレームごとの経過時間
*/
void ObjPlayer::AnimSet(MOTION motion, float deltaTime) {
	model_->SetTrackEnable(motion, true);
	model_->AdvanceTime(deltaTime);
}

/**
* @brief 自身の状態に合ったアニメーションを返す
* @return アニメーション
*/
ObjPlayer::MOTION ObjPlayer::AnimChange() {
	return hasBall_ ? MOTION::HAND : MOTION::STAND;
}

/**
* @brief 発射処理
* @brief ballID ボールのID
*/
void ObjPlayer::Shoting(const int ballID) {
	hasBall_ = false;
	myBallID_ = -1;
	instructor_->Shot(ballID, forward_);
}

/**
* @brief ボールをキャッチする処理
* @param ballID ボールのID
*/
void ObjPlayer::CautchedBall(const int ballID) {
	hasBall_ = true;
	myBallID_ = ballID;
	instructor_->Cautch(id_my_, myBallID_);
}

/**
* @brief 手元の座標を返す
* @return 手元の座標
*/
Vector2 ObjPlayer::Get_HandPos() {
	XMFLOAT2 _handForward;
	_handForward.x = std::cosf(6) * std::cosf(strategy_->GetRotateX()) - std::sinf(6) * std::sinf(strategy_->GetRotateX());
	_handForward.y = std::sinf(6) * std::cosf(strategy_->GetRotateX()) + std::cosf(6) * std::sinf(strategy_->GetRotateX());
	return (pos_ + POS_HAND * _handForward);
}

/**
* @brief 戦闘状態の処理
* @param deltaTime フレームごとの経過時間
*/
void ObjPlayer::Playing(const float deltaTime) {
	AnimReset();
	AnimSet(AnimChange(), deltaTime);

	strategy_->Update(deltaTime);
	barrier_->Update(deltaTime);

	AssignPosition();
	rotate_ = Vector2(strategy_->GetRotateX(), GAME_CONST.Player_FacingRight);
	forward_ = Vector2(std::cosf(rotate_.x), std::sinf(rotate_.x));

	FIELD::ClampLoop(pos_);

	SetTransforms(pos_, rotate_);

	UpdateToMorton();

	HitAction(GetHitObject());
}

/**
* @brief やられた状態の処理
* @param deltaTime フレームごとの経過時間
*/
void ObjPlayer::Beaten(const float deltaTime) {
	ti_respone_->Update(deltaTime);

	// 復活
	if (ti_respone_->TimeOut()) {
		ti_respone_->Reset();
		barrier_->DisprayOn();
		SetTransforms(pos_, rotate_);
		AssignPosition();
		UpdateToMorton();
		isDown_ = false;
	}
}