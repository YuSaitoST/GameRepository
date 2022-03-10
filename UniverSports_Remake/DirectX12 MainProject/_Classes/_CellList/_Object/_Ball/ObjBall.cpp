#include "ObjBall.h"

ObjBall::ObjBall() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, Vector3::Zero, 0.0f);

	state_ = nullptr;
	rotate_ = Vector2::Zero;
	pos_z_ = 0.0f;
}

ObjBall::ObjBall(Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(BALL, pos, r);

	state_ = new StFloat();
	rotate_ = Vector2::Zero;
	pos_z_ = 0.0f;
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

	ObjectBase::Update();
}

void ObjBall::Render(DX9::MODEL& model) {
	model->SetPosition(Vector3(pos_.x, pos_.y, pos_z_));
	model->SetRotation(Vector3(rotate_.x, rotate_.y, 0.0f));
	/*model->SetMaterial()*/
	model->Draw();
}

void ObjBall::AddPower(Vector3 forward, float speed) {
	physics_->SetLinerVelocity(forward * speed);
	physics_->SetCenterOfMassTransform(Vector3(pos_.x, pos_.y, 0.0f), Vector3(0.0f, 0.0f, 0.0f));

	pos_ = physics_->GetCenterOfMassPosition();
	SetTransforms();
}

void ObjBall::SetTransforms() {
	collision_->SetPosition(Vector3(pos_.x, pos_.y, 0.0f));
	physics_->SetTransform(Vector3(pos_.x, pos_.y, 0.0f), Vector3(rotate_.x, rotate_.y, 0.0f));
}