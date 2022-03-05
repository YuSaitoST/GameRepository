#include "btObject.h"

btObject::btObject(SimpleMath::Vector3 pos) {
	bt_collision_ = new btSphereShape(0.8f);

	btVector3    _pos(pos.x, pos.y, 0.0f);
	btQuaternion _rot(0.0f, 0.0f, 0.0f, 1.0f);
	bt_state_ = new btDefaultMotionState(btTransform(_rot, _pos));

	btScalar	_mass = 1.0f;
	btVector3	_inertia(0.0f, 0.0f, 0.0f);
	bt_body_ = new btRigidBody(_mass, bt_state_, bt_collision_, _inertia);

	// スリープモードを解除（操作不可バグを直せる）
	bt_body_->setActivationState(DISABLE_DEACTIVATION);

	bt_body_->setRestitution(0.9f);

	velocity_ = SimpleMath::Vector3::Zero;
}

btObject::~btObject() {
	delete bt_body_;
	delete bt_state_;
	delete bt_collision_;
}

void btObject::SetTransform(SimpleMath::Vector3 pos, SimpleMath::Vector3 rotate) {
	btVector3		_pos(pos.x, pos.y, 0.0f);
	btQuaternion	_rot(rotate.x, rotate.y, rotate.z);
	bt_body_->setCenterOfMassTransform(btTransform(_rot, _pos));
}

void btObject::Moving(SimpleMath::Vector3 power) {
	const btVector3 _inertia(power.x, power.y, 0.0f);
	bt_body_->applyCentralImpulse(_inertia);
	LimitSpeed();
}

void btObject::LimitSpeed() {
	velocity_ = (XMFLOAT3)bt_body_->getLinearVelocity();

	// 通常速度制限
	if (GAME_CONST.PL_SPEED_MAX < velocity_.Length()) {
		velocity_.Normalize();
		velocity_ *= GAME_CONST.PL_SPEED_MAX;
	}

	bt_body_->setLinearVelocity(*(btVector3*)&velocity_);
}