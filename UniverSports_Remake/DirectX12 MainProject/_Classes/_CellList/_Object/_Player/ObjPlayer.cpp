#include "ObjPlayer.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_UI/_CharaIcon/IconAnimator.h"
#include "_Classes/_CellList/_HitInstructor/HitInstructor.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "DontDestroyOnLoad.h"

ObjPlayer::ObjPlayer() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, NONE_COLLI_TYPE, Vector3::Zero, 0.0f);

	physics_ = new btObject(NONE_BULLET_TYPE, Vector3::Zero, Vector3::Zero, 0.0f, 0.0f);
	handForward_ = Vector2::Zero;
	life_ = nullptr;
	ti_respone_ = nullptr;
	eff_down_ = nullptr;
	strategy_ = nullptr;
	targetObj_ = nullptr;
	id_team_ = -1;
	myBallID_ = -1;
	hasBall_ = false;
	isDown_ = false;
}

ObjPlayer::ObjPlayer(OPERATE_TYPE strategy, Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(PLAYER, COLLI_TYPE::SPHRER, pos, r);

	physics_ = new btObject(BULLET_TYPE::BT_SPHRER, pos, Vector3::Zero, 0.0f, 1.0f);
	rotate_ = Vector2(0.0f, GAME_CONST.Player_FacingRight);
	handForward_ = Vector2::Zero;
	targetObj_ = nullptr;
	id_team_ = -1;
	myBallID_ = -1;
	hasBall_ = false;
	isDown_ = false;

	life_ = new MyLife(3);
	ti_respone_ = new OriTimer(GAME_CONST.PL_ReSponeTime);
	eff_down_ = new EffDown();
	
	strategy_ = (strategy == OPERATE_TYPE::MANUAL)	 ? static_cast<CharaStrategy*>(new ManualChara())   : 
				(strategy == OPERATE_TYPE::COMPUTER) ? static_cast<CharaStrategy*>(new ComputerChara()) : nullptr;
}

ObjPlayer::~ObjPlayer() {
	if (strategy_ != nullptr)
		delete strategy_;

	delete eff_down_;
	delete ti_respone_;
	delete life_;
	delete physics_;
}

void ObjPlayer::Initialize(const int id) {
	strategy_->Initialize(id, this);
	eff_down_->Initialize("Down" + std::to_string(id));
	physics_->SetActivationState(DISABLE_DEACTIVATION);

	id_my_ = id;
	id_team_ = (DontDestroy->GameMode_.isDODGEBALL_2ON2()) ? -1 : id_my_;
}

void ObjPlayer::LoadAssets(std::wstring file_name) {
	strategy_->LoadAssets();
	eff_down_->LoadAsset(L"_Effects\\_Down\\HITeffect.efk");

	CreateModel(file_name.c_str());
	
	collision_->SetColli(model_->GetBoundingSphere());
	collision_->SetColliScale(1.2f);

	AssignPosition();
	rotate_ = Vector2(strategy_->GetRotateX(), GAME_CONST.Player_FacingRight);
	forward_ = strategy_->GetForward();
	r_ = model_->GetBoundingSphere().Radius;

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

void ObjPlayer::HitAction(ObjectBase* hitObject) {
	// �Փ˂������̂��Ȃ��Ȃ瑁�����^�[��
	if (hitObject == nullptr)
		return;

	const OBJ_TYPE _type = hitObject->myObjectType();

	if (_type == BALL) {
		ObjBall* _ball = dynamic_cast<ObjBall*>(hitObject);  // �{�[���̏�Ԃ�m�邽�߂Ƀ_�E���L���X�g

		if (id_my_ == _ball->GetOwnerID())  // ���������{�[���Ƃ̓����蔻��͎��K�v�Ȃ�
			return;

		const ObjBall::STATE _baleState = _ball->NowState();

		if (_baleState == _ball->STATE::FLOAT) {  // �L���b�`����
			if (hasBall_ && myBallID_ != -1)
				return;

			CautchedBall(_ball->myObjectID());
		}
		else if (_baleState == _ball->STATE::SHOT) {  // ���ꏈ��
			life_->TakeDamage();
			eff_down_->PlayOneShot();
			eff_down_->Set_Position(Vector3(pos_.x, pos_.y, 0.0f));

			SetTransforms(Vector2(99.0f, 99.0f), rotate_);
			pos_ = Vector2(GAME_CONST.S_POS[id_my_].x, GAME_CONST.S_POS[id_my_].y);

			isDown_ = true;

			if (life_->NowLifePoint() <= 0)
				DontDestroy->Survivor_[id_my_] = false;

			IconAnimator::DisplayOn();
			HitInstructor::BallBreakOfThrower(_ball->myObjectID());

			if (hasBall_) {
				HitInstructor::BallBreakOfTheHitter(myBallID_);
				myBallID_ = -1;
				hasBall_ = false;
			}
		}
	}
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

void ObjPlayer::AsjustmentForward() {
	forward_ *= 1.5f;
}

void ObjPlayer::Shoting(const int ballID) {
	hasBall_ = false;
	myBallID_ = -1;
	HitInstructor::BallShot(ballID, forward_);
}

void ObjPlayer::CautchedBall(const int ballID) {
	hasBall_ = true;
	myBallID_ = ballID;
	HitInstructor::BallCautch(id_my_, myBallID_);
}

Vector2 ObjPlayer::Get_HandPos() {
	const Vector2 _dir = strategy_->GetForward();
	const int _dir_x = std::roundf(_dir.x), _dir_y = std::roundf(_dir.y);

	handForward_.x = std::cosf(6) * std::cosf(strategy_->GetRotateX()) - std::sinf(6) * std::sinf(strategy_->GetRotateX());
	handForward_.y = std::sinf(6) * std::cosf(strategy_->GetRotateX()) + std::cosf(6) * std::sinf(strategy_->GetRotateX());
	return (pos_ + handForward_ * POS_HAND);
}

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

	HitAction(GetHitObject());
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