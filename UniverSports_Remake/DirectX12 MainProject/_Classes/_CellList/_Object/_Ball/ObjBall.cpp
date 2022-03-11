#include "ObjBall.h"

ObjBall::ObjBall() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, Vector3::Zero, 0.0f);

	colorType_ = NOMAL_COLOR;
	state_ = nullptr;
	rotate_ = Vector2::Zero;
	pos_z_ = 0.0f;
	id_owner_ = -1;
	isInPlayerHands_ = false;
}

ObjBall::ObjBall(Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(BALL, pos, r);

	SwitchState(FLOAT);

	colorType_ = NOMAL_COLOR;
	rotate_ = Vector2::Zero;
	pos_z_ = 0.0f;
	id_owner_ = -1;
	isInPlayerHands_ = false;
}

ObjBall::~ObjBall() {

}

void ObjBall::Initialize(const int id) {
	state_->Initialize();

	pos_		= state_->GetPosition();
	forward_	= state_->GetForward();

	id_my_		= id;
}

void ObjBall::LoadAssets(DX9::MODEL& model) {
	collision_->SetColli(model->GetBoundingSphere());

	AddPower(Vector3(forward_.x, forward_.y, 0.0f), GAME_CONST.BA_SPEED_FLOAT);

	pos_ = physics_->GetCenterOfMassPosition();
	SetTransforms();
}

void ObjBall::Update(const float deltaTime) {
	state_->Update(this);

	pos_ = physics_->GetCenterOfMassPosition();
	SetTransforms();

	UpdateToMorton();

	ObjectBase* _obj = IsHitObject();
	if (_obj != nullptr) {
		if (_obj->myObjectType() == OBJ_TYPE::PLAYER) {
			isInPlayerHands_ = true;
		}
	}
}

void ObjBall::Render(DX9::MODEL& model) {
	model->SetPosition(Vector3(pos_.x, pos_.y, pos_z_));
	model->SetRotation(Vector3(rotate_.x, rotate_.y, 0.0f));
	model->SetMaterial(ChangeMaterial(colorType_));
	model->Draw();
}

void ObjBall::SwitchState(STATE state) {
	switch (state) {
		case FLOAT	: state_ = new StFloat();		 break;
		case CAUTCH	: state_ = new StCautch();		 break;
		default		: assert(!"ObjBall_不正な状態"); break;
	}
}

void ObjBall::SwitchColor(COLOR_TYPE colorType) {
	colorType_ = colorType;
}

D3DMATERIAL9 ObjBall::ChangeMaterial(COLOR_TYPE colorType) {
	D3DMATERIAL9 _mat{};

	switch (colorType) {
		case NOMAL_COLOR:
			_mat = GetNomMaterial(); 
			break;
		case PLAYER_COLOR:
			_mat.Diffuse = P_DIFFUSE[id_owner_];
			_mat.Ambient = P_AMBIENT;
			break;
		case TEAM_COLOR:
			break;
		default:
			assert(!"ObjBall : 不正な色指定"); 
			break;
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