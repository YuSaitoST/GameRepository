#include "ObjPlayer.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"

ObjPlayer::ObjPlayer() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, Vector3::Zero, 0.0f);

	handForward_ = Vector2::Zero;
	life_ = nullptr;
	ti_respone_ = nullptr;
	eff_down_ = nullptr;
	strategy_ = nullptr;
	myBall_ = nullptr;
	targetObj_ = nullptr;
	hasBall_ = false;
	isDown_ = false;
}

ObjPlayer::ObjPlayer(OPERATE_TYPE strategy, Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(PLAYER, pos, r);

	rotate_ = Vector2(0.0f, GAME_CONST.Player_FacingRight);
	handForward_ = Vector2::Zero;
	myBall_ = nullptr;
	targetObj_ = nullptr;
	hasBall_ = false;
	isDown_ = false;

	life_ = new MyLife(3);
	ti_respone_ = new OriTimer(GAME_CONST.PL_ReSponeTime);
	eff_down_ = new EffDown();
	
	strategy_ = (strategy == OPERATE_TYPE::MANUAL)	 ? static_cast<CharaStrategy*>(new ManualChara())   : 
				(strategy == OPERATE_TYPE::COMPUTER) ? static_cast<CharaStrategy*>(new ComputerChara()) : nullptr;
	//if (strategy == OPERATE_TYPE::MANUAL)
	//	strategy_ = new ManualChara();
	//else if (strategy == OPERATE_TYPE::COMPUTER)
	//	strategy_ = new ComputerChara();
	//else
	//	strategy_ = nullptr;
}

ObjPlayer::~ObjPlayer() {
	if (strategy_ != nullptr)
		delete strategy_;

	delete eff_down_;
	delete ti_respone_;
	delete life_;
}

void ObjPlayer::Initialize(const int id) {
	strategy_->Initialize(id, this);
	eff_down_->Initialize("Down" + std::to_string(id));

	id_my_ = id;
}

void ObjPlayer::LoadAssets(std::wstring file_name) {
	strategy_->LoadAssets();
	eff_down_->LoadAsset(L"_Effects\\_Down\\HITeffect.efk");

	model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, file_name.c_str());
	model_->SetScale(0.018f);
	model_->SetMaterial(GetNomMaterial());
	
	collision_->SetColli(model_->GetBoundingSphere());
	collision_->SetColliScale(1.2f);

	AssignPosition();
	rotate_ = Vector2(strategy_->GetRotateX(), GAME_CONST.Player_FacingRight);
	forward_ = strategy_->GetForward();
	r_ = model_->GetBoundingSphere().Radius;

	ClampLoop(pos_);

	SetTransforms(pos_, rotate_);
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

void ObjPlayer::SetTransforms(const Vector2 pos, const Vector2 rotate) {
	model_->SetPosition(Vector3(pos.x, pos.y, 0.0f));
	model_->SetRotation(Vector3(rotate.x, rotate.y, 0.0f));
	collision_->SetPosition(Vector3(pos.x, pos.y, 0.0f));
	physics_->SetTransform(Vector3(pos.x, pos.y, 0.0f), Vector3(rotate.x, rotate.y, 0.0f));
}

void ObjPlayer::AnimReset() {
	for (int i = 0; i < 6; i++)
		model_->SetTrackEnable(i, false);
}

void ObjPlayer::AnimSet(MOTION motion, float deltaTime) {
	model_->SetTrackEnable(motion, true);
	model_->AdvanceTime(deltaTime);
}

ObjPlayer::MOTION ObjPlayer::AnimChange() {
	if (hasBall_)
		return MOTION::HAND;
	else
		return MOTION::STAND;
}

void ObjPlayer::Shoting(ObjBall* ball) {
	hasBall_ = false;
	myBall_->Shoting(forward_);
	myBall_ = nullptr;
}

Vector2 ObjPlayer::Get_HandPos() {
	const Vector2 _dir = strategy_->GetForward();
	const int _dir_x = std::roundf(_dir.x), _dir_y = std::roundf(_dir.y);

	handForward_.x = std::cosf(6) * std::cosf(strategy_->GetRotateX()) - std::sinf(6) * std::sinf(strategy_->GetRotateX());
	handForward_.y = std::sinf(6) * std::cosf(strategy_->GetRotateX()) + std::cosf(6) * std::sinf(strategy_->GetRotateX());
	return (pos_ + handForward_ * POS_HAND);
}

/*
* stateパターンにした方が良さそうな部分
*/

void ObjPlayer::Playing(const float deltaTime) {
	AnimReset();
	AnimSet(AnimChange(), deltaTime);

	strategy_->Update(deltaTime);

	AssignPosition();
	rotate_ = Vector2(strategy_->GetRotateX(), GAME_CONST.Player_FacingRight);
	forward_ = strategy_->GetForward();

	ClampLoop(pos_);

	SetTransforms(pos_, rotate_);

	UpdateToMorton();

	if (id_my_ == 0 && myBall_ != nullptr)
		return;

	ObjectBase* _obj = IsHitObject();
	if (_obj != nullptr) {
		if (_obj->myObjectType() == OBJ_TYPE::BALL) {
			ObjBall* _ball = dynamic_cast<ObjBall*>(_obj);

			// やられ処理
			if (_ball->NowState() == _ball->STATE::SHOT) {
				if (_ball->GetOwnerID() == id_my_)
					return;

				life_->TakeDamage();
				eff_down_->PlayOneShot();
				eff_down_->Set_Position(Vector3(pos_.x, pos_.y, 0.0f));
				isDown_ = true;

				SetTransforms(Vector2(99.0f, 99.0f), rotate_);
				pos_ = Vector2::Zero;

				return;
			}
			// キャッチ処理
			else if (_ball->NowState() == _ball->STATE::FLOAT) {
				if (myBall_ != nullptr)
					return;

				myBall_ = _ball;

				if (myBall_->GetOwnerID() != -1) {
					myBall_ = nullptr;
					return;
				}

				myBall_->SetOwnerID(id_my_);
				hasBall_ = true;
			}
		}
	}
}

void ObjPlayer::Beaten(const float deltaTime) {
	ti_respone_->Update(deltaTime);

	if (ti_respone_->TimeOut()) {
		ti_respone_->ResetCountTime();
		SetTransforms(pos_, rotate_);
		AssignPosition();
		isDown_ = false;
	}
}