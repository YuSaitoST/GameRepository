#include "ObjPlayer.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"

ObjPlayer::ObjPlayer() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, Vector3::Zero, 0.0f);

	rotate_ = Vector2::Zero;
	forward_ = Vector2::Zero;
	strategy_ = nullptr;
	myBall_ = nullptr;
	hasBall_ = false;
}

ObjPlayer::ObjPlayer(OPERATE_TYPE strategy, Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(PLAYER, pos, r);

	rotate_ = Vector2(0.0f, GAME_CONST.Player_FacingRight);
	forward_ = Vector2::Zero;
	myBall_ = nullptr;
	hasBall_ = false;

	if (strategy == OPERATE_TYPE::MANUAL)
		strategy_ = new ManualChara();
	else if (strategy == OPERATE_TYPE::COMPUTER)
		strategy_ = new ComputerChara();
	else
		strategy_ = nullptr;
}

ObjPlayer::~ObjPlayer() {
	if (strategy_ != nullptr)
		delete strategy_;
}

void ObjPlayer::Initialize(const int id) {
	strategy_->Initialize(id, this);

	id_my_ = id;
}

void ObjPlayer::LoadAssets(std::wstring file_name) {
	strategy_->LoadAssets();

	model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, file_name.c_str());
	model_->SetScale(0.018f);
	model_->SetMaterial(GetNomMaterial());

	collision_->SetColli(model_->GetBoundingSphere());
	collision_->SetColliScale(1.2f);

	SetTransforms();
}

void ObjPlayer::Update(const float deltaTime) {
	AnimReset();
	AnimSet(AnimChange(), deltaTime);

	strategy_->Update(deltaTime);


	AssignPosition();
	rotate_ = Vector2(strategy_->GetRotateX(), GAME_CONST.Player_FacingRight);

	ClampLoop(pos_);

	SetTransforms();

	UpdateToMorton();

	ObjectBase* _obj = IsHitObject();
	if (_obj != nullptr) {
		if (_obj->myObjectType() == OBJ_TYPE::BALL) {
			if (myBall_ != nullptr)
				return;

			myBall_ = dynamic_cast<ObjBall*>(_obj);

			if (myBall_->GetOwnerID() != -1) {
				myBall_ = nullptr;
				return;
			}

			myBall_->SetOwnerID(id_my_);
			hasBall_ = true;
		}
	}

	if (isHit_) {
		D3DMATERIAL9 mate{};
		mate.Diffuse = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 1.0f);
		model_->SetMaterial(mate);
	}
	else {
		model_->SetMaterial(GetNomMaterial());
	}
}

void ObjPlayer::Render() {
	model_->Draw();
}

void ObjPlayer::UIRender() {
	strategy_->UIRender();
}

void ObjPlayer::SetTransforms() {
	model_->SetPosition(Vector3(pos_.x, pos_.y, 0.0f));
	model_->SetRotation(Vector3(rotate_.x, rotate_.y, 0.0f));
	collision_->SetPosition(Vector3(pos_.x, pos_.y, 0.0f));
	physics_->SetTransform(Vector3(pos_.x, pos_.y, 0.0f), Vector3(rotate_.x, rotate_.y, 0.0f));
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