#pragma once

#include <btBulletDynamicsCommon.h>
#include "Base/pch.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

using namespace DirectX;

class btObject {
public:
	btObject(SimpleMath::Vector3 pos);
	virtual ~btObject();

	void SetTransform(SimpleMath::Vector3 pos, SimpleMath::Vector3 rotate);
	void Moving(SimpleMath::Vector3 power);
	void LimitSpeed();

	inline btRigidBody* Get_RigidBody() const { return bt_body_; };
	
	inline SimpleMath::Vector2 GetCenterOfMassPosition() {
		const SimpleMath::Vector3 pos = (XMFLOAT3)bt_body_->getCenterOfMassPosition();
		return SimpleMath::Vector2(pos.x, pos.y);
	}

	inline SimpleMath::Vector2 GetLinearVelocity() {
		const SimpleMath::Vector3 vel = (XMFLOAT3)bt_body_->getLinearVelocity();
		return SimpleMath::Vector2(vel.x, vel.y);
	}

private:
	btCollisionShape*		bt_collision_;
	btDefaultMotionState*	bt_state_;
	btRigidBody*			bt_body_;

	SimpleMath::Vector3		velocity_;
};