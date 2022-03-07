#include "ObjPlayer.h"

ObjPlayer::ObjPlayer() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, Vector3::Zero, 0.0f);

	rotate_ = Vector2::Zero;
	motion_ = STAND;
	strategy_ = nullptr;
}

ObjPlayer::ObjPlayer(OPERATE_TYPE strategy, Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(PLAYER, pos, r);

	rotate_ = Vector2(0.0f, GAME_CONST.Player_FacingRight);
	motion_ = STAND;

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
	AnimSet(motion_, deltaTime);

	strategy_->Update(deltaTime);


	AssignPosition();
	rotate_ = Vector2(strategy_->GetRotateX(), GAME_CONST.Player_FacingRight);

	ClampLoop(pos_);

	SetTransforms();

	ObjectBase::Update();

	/*“–‚½‚Á‚½‚ç‚â‚éˆ—‚Í‚±‚±‚É‘‚­‚Æ—Ç‚³‚»‚¤*/
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

void ObjPlayer::AnimReset() {
	for (int i = 0; i < 6; i++)
		model_->SetTrackEnable(i, false);
}

void ObjPlayer::AnimSet(MOTION motion, float deltaTime) {
	model_->SetTrackEnable(motion, true);
	model_->AdvanceTime(deltaTime);
}

void ObjPlayer::SetTransforms() {
	model_->SetPosition(Vector3(pos_.x, pos_.y, 0.0f));
	model_->SetRotation(Vector3(rotate_.x, rotate_.y, 0.0f));
	collision_->SetPosition(Vector3(pos_.x, pos_.y, 0.0f));
	physics_->SetTransform(Vector3(pos_.x, pos_.y, 0.0f), Vector3(rotate_.x, rotate_.y, 0.0f));
}