#include "ObjBall.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "DontDestroyOnLoad.h"

float ObjBall::pos_z_smallest_;

ObjBall::ObjBall() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, NONE_COLLI_TYPE, Vector3::Zero, 0.0f);

	physics_ = new btObject(NONE_BULLET_TYPE, Vector3::Zero, Vector3::Zero, 0.0f, 0.0f);
	colorType_ = DEFAULT_COLOR;
	state_ = nullptr;
	pos_z_ = 0.0f;
	id_owner_ = -1;
	isInPlayerHands_ = false;
	isBreak_ = false;
}

ObjBall::ObjBall(Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(BALL, COLLI_TYPE::SPHRER, pos, r);

	st_float_ = new StFloat();
	st_cautch_ = new StCautch();
	st_shot_ = new StShot();
	st_standby_ = new StStandby();

	SwitchState(STANDBY);

	physics_ = new btObject(BULLET_TYPE::BT_SPHRER, pos, Vector3::Zero, 0.0f, 1.0f);
	colorType_ = DEFAULT_COLOR;
	pos_z_ = 0.0f;
	id_owner_ = -1;
	isInPlayerHands_ = false;
	isBreak_ = false;

}

ObjBall::~ObjBall() {
	delete physics_;
	delete st_standby_;
	delete st_shot_;
	delete st_cautch_;
	delete st_float_;
}

void ObjBall::Initialize(const int id) {
	st_float_->Initialize();
	st_cautch_->Initialize();
	st_shot_->Initialize();
	st_standby_->Initialize();

	physics_->SetActivationState(DISABLE_DEACTIVATION);

	pos_		= state_->GetPosition();
	forward_	= state_->GetForward();

	id_my_		= id;
}

void ObjBall::LoadAssets(DX9::MODEL& model) {
	collision_->SetColli(model->GetBoundingSphere());

	AddPower(Vector3(forward_.x, forward_.y, 0.0f), GAME_CONST.BA_SPEED_FLOAT);
	
	pos_ = physics_->GetCenterOfMassPosition();
	SetTransforms();

	r_ = model->GetBoundingSphere().Radius;
}

void ObjBall::Update(const float deltaTime) {
	state_->Update(this);

	pos_ = physics_->GetCenterOfMassPosition();
	SetTransforms();

	UpdateToMorton();
}

void ObjBall::Render(DX9::MODEL& model) {
	model->SetPosition(Vector3(pos_.x, pos_.y, pos_z_));
	model->SetRotation(Vector3(rotate_.x, rotate_.y, 0.0f));
	model->SetMaterial(ChangeMaterial(colorType_));
	model->Draw();
}

void ObjBall::SwitchState(B_STATE state) {
	switch (state) {
		case STANDBY	: state_ = &*st_standby_;			break;
		case FLOATING	: state_ = &*st_float_;				break;
		case CAUTCH		: state_ = &*st_cautch_;			break;
		case SHOT		: state_ = &*st_shot_;				break;
		case GOAL		: state_ = &*st_goal_;				break;
		default			: assert(!"ObjBall_不正な状態");	break;
	}
}

void ObjBall::SwitchColor(COLOR_TYPE colorType) {
	colorType_ = colorType;
}

D3DMATERIAL9 ObjBall::ChangeMaterial(COLOR_TYPE colorType) {
	D3DMATERIAL9 _mat{};

	switch (colorType) {
		case DEFAULT_COLOR : _mat = GetNomMaterial(); break;
		case PLAYERS_COLOR : _mat.Diffuse = P_DIFFUSE[std::min(std::max(0, DontDestroy->ChoseColor_[id_owner_]), 4 - 1)]; _mat.Ambient = P_AMBIENT; break;
		case TEAM_COLOR    : break;
		default			   : assert(!"ObjBall_assert : 不正な色指定"); break;
	}

	return _mat;
}

void ObjBall::AddPower(Vector3 forward, float speed) {
	physics_->SetLinerVelocity(forward * speed);
	physics_->SetCenterOfMassTransform(Vector3(pos_.x, pos_.y, pos_z_), Vector3::Zero);

	pos_ = physics_->GetCenterOfMassPosition();
	SetTransforms();
}

void ObjBall::SetTransforms() {
	collision_->SetPosition(Vector3(pos_.x, pos_.y, pos_z_));
	physics_->SetTransform(Vector3(pos_.x, pos_.y, pos_z_), Vector3(rotate_.x, rotate_.y, 0.0f));
}

void ObjBall::WasCaught(const int ownerID) {
	id_owner_ = ownerID;
	isInPlayerHands_ = true;
	ResetVelocity();
	AssignTransform(Vector3(pos_.x, pos_.y, pos_z_smallest_), forward_);
	SwitchColor(PLAYERS_COLOR);
}

void ObjBall::WasThrown(Vector2 forward) {
	forward_ = forward;
	isInPlayerHands_ = false;
	AddPower(Vector3(forward_.x, forward_.y, 0.0f), GAME_CONST.BA_SPEED_SHOT);
}

void ObjBall::WasGuessed() {
	DontDestroy->Score_[id_owner_] += 1;
	BallBreak();
}

void ObjBall::BallBreak() {
	id_owner_ = -1;
	isBreak_ = true;
	isInPlayerHands_ = false;
	AssignTransform(Vector3(GAME_CONST.FieldSide_X, GAME_CONST.FieldSide_Y, 0.0f), Vector2::Zero);
}