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
* @brief �Փˎ��̏���
* @param hitObject �Փ˂�������
*/
void ObjPlayer::HitAction(ObjectBase* hitObject) {
	// �Փ˂������̂��Ȃ��Ȃ瑁�����^�[��
	if (hitObject == nullptr)
		return;

	const OBJ_TYPE _type = hitObject->myObjectType();

	// �^�C�v�ʂ̏Փ˔���
	if (_type == BALL) {
		ObjBall* _ball = dynamic_cast<ObjBall*>(hitObject);  // �{�[���̏�Ԃ�m�邽�߂Ƀ_�E���L���X�g

		if (id_my_ == _ball->GetOwnerID())  // ���������{�[���Ƃ̓����蔻��͎��K�v�Ȃ�
			return;

		const B_STATE _baleState = _ball->NowState();

		if (_baleState == B_STATE::FLOATING) {  // �L���b�`����
			// �{�[���������Ă��銎�ێ��{�[����ID�����݂���
			if (hasBall_ && myBallID_ != -1)
				return;

			CautchedBall(_ball->myObjectID());
		}
		else if (_baleState == B_STATE::SHOT) {  // ���ꏈ��

			// �o���A���o�Ă���Ȃ�
			if (barrier_->IsDisplayed())
				return;

			// �����`�[���̃����o�[���������{�[���̓q�b�g���Ȃ�
			if (teamID_->Get(_ball->GetOwnerID()) == teamID_->Get())
				return;

			eff_down_->PlayOneShot();
			eff_down_->Set_Position(Vector3(pos_.x, pos_.y, 0.0f));

			// �����蔻����������߂ɁA��U���炩�ɏ�O�Ȉʒu�ֈړ�������
			SetTransforms(Vector2(99.0f, 99.0f), rotate_);
			pos_ = Vector2(GAME_CONST.S_POS[id_my_].x, GAME_CONST.S_POS[id_my_].y);

			isDown_ = true;

			// �S�[����p���郂�[�h�ł̓��C�t�̏����͂Ȃ�
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
* @brief ���W�Ɖ�]���Z�b�g����
* @param pos ���W
* @param rotate ��]
*/
void ObjPlayer::SetTransforms(XMFLOAT2 pos, XMFLOAT2 rotate) {
	model_->SetPosition(Vector3(pos.x, pos.y, 0.0f));
	model_->SetRotation(Vector3(rotate.x, rotate.y, 0.0f));
	barrier_->SetPosition(Vector3(pos.x, pos.y, 0.0f));
	SetTransform(XMFLOAT3(pos.x, pos.y, 0.0f), rotate);
}

/**
* @brief ���f������
* @param fileName �t�@�C����
*/
void ObjPlayer::CreateModel(std::wstring fileName) {
	model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, fileName.c_str());
	model_->SetScale(PLAYER_PARAM.SCALE);
	model_->SetMaterial(GetNomMaterial());
}

/**
* @brief �A�j���[�V���������Z�b�g����
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
* @brief �A�j���[�V�������Z�b�g����
* @param motion �A�j���[�V����
* @param deltaTime �t���[�����Ƃ̌o�ߎ���
*/
void ObjPlayer::AnimSet(MOTION motion, float deltaTime) {
	model_->SetTrackEnable(motion, true);
	model_->AdvanceTime(deltaTime);
}

/**
* @brief ���g�̏�Ԃɍ������A�j���[�V������Ԃ�
* @return �A�j���[�V����
*/
ObjPlayer::MOTION ObjPlayer::AnimChange() {
	return hasBall_ ? MOTION::HAND : MOTION::STAND;
}

/**
* @brief ���ˏ���
* @brief ballID �{�[����ID
*/
void ObjPlayer::Shoting(const int ballID) {
	hasBall_ = false;
	myBallID_ = -1;
	instructor_->Shot(ballID, forward_);
}

/**
* @brief �{�[�����L���b�`���鏈��
* @param ballID �{�[����ID
*/
void ObjPlayer::CautchedBall(const int ballID) {
	hasBall_ = true;
	myBallID_ = ballID;
	instructor_->Cautch(id_my_, myBallID_);
}

/**
* @brief �茳�̍��W��Ԃ�
* @return �茳�̍��W
*/
Vector2 ObjPlayer::Get_HandPos() {
	XMFLOAT2 _handForward;
	_handForward.x = std::cosf(6) * std::cosf(strategy_->GetRotateX()) - std::sinf(6) * std::sinf(strategy_->GetRotateX());
	_handForward.y = std::sinf(6) * std::cosf(strategy_->GetRotateX()) + std::cosf(6) * std::sinf(strategy_->GetRotateX());
	return (pos_ + POS_HAND * _handForward);
}

/**
* @brief �퓬��Ԃ̏���
* @param deltaTime �t���[�����Ƃ̌o�ߎ���
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
* @brief ���ꂽ��Ԃ̏���
* @param deltaTime �t���[�����Ƃ̌o�ߎ���
*/
void ObjPlayer::Beaten(const float deltaTime) {
	ti_respone_->Update(deltaTime);

	// ����
	if (ti_respone_->TimeOut()) {
		ti_respone_->Reset();
		barrier_->DisprayOn();
		SetTransforms(pos_, rotate_);
		AssignPosition();
		UpdateToMorton();
		isDown_ = false;
	}
}