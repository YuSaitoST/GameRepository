#include "btObject.h"

btObject::btObject(BULLET_TYPE type, SimpleMath::Vector3 pos, SimpleMath::Vector3 scale, float rotZ, float mass) {
	bt_collision_ = (type == BT_SPHRER) ? (btCollisionShape*)(new btSphereShape(0.8f)) : (type == BOX) ? (btCollisionShape*)(new btBoxShape(btVector3(scale.x, scale.y, scale.z))) : nullptr;
	
	btVector3    _pos(pos.x, pos.y, 0.0f);
	btQuaternion _rot(0.0f, 0.0f, rotZ, 1.0f);
	bt_state_ = new btDefaultMotionState(btTransform(_rot, _pos));

	btScalar	_mass = mass;
	btVector3	_inertia(0.0f, 0.0f, 0.0f);
	bt_body_ = new btRigidBody(_mass, bt_state_, bt_collision_, _inertia);

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

	// ë¨ìxêßå¿
	if (GAME_CONST.PL_SPEED_MAX < velocity_.Length()) {
		velocity_.Normalize();
		velocity_ *= GAME_CONST.PL_SPEED_MAX;
	}

	bt_body_->setLinearVelocity(*(btVector3*)&velocity_);
}