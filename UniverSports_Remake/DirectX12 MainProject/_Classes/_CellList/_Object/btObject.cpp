#include "btObject.h"

btObject::btObject(BULLET_TYPE type, SimpleMath::Vector3 pos, SimpleMath::Vector3 scale, float rotZ, float mass) {
	//! 球体形状
	btCollisionShape* _bt_collision;

	//! 位置・姿勢
	btDefaultMotionState* _bt_state;


	_bt_collision = (type == BT_SPHRER) ? (btCollisionShape*)(new btSphereShape(0.8f)) : (type == BT_BOX) ? (btCollisionShape*)(new btBoxShape(btVector3(scale.x, scale.y * 0.125f, scale.z))) : nullptr;
	
	btVector3    _pos(pos.x, pos.y, 0.0f);
	btQuaternion _rot(0.0f, 0.0f, rotZ, 1.0f);
	_bt_state = new btDefaultMotionState(btTransform(_rot, _pos));

	btScalar	_mass = mass;
	btVector3	_inertia(0.0f, 0.0f, 0.0f);
	bt_body_ = new btRigidBody(_mass, _bt_state, _bt_collision, _inertia);

	bt_body_->setRestitution(0.9f);
}

btObject::~btObject() {
	delete bt_body_;
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
	SimpleMath::Vector3 _velocity = (XMFLOAT3)bt_body_->getLinearVelocity();

	// 速度制限
	if (PLAYER_PARAM.SPEED_MAX_NORMAL < _velocity.Length()) {
		_velocity.Normalize();
		_velocity *= PLAYER_PARAM.SPEED_MAX_NORMAL;
	}

	bt_body_->setLinearVelocity(*(btVector3*)&_velocity);
}