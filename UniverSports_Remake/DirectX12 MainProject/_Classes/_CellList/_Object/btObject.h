/**
 * @file btObject.h
 * @brief Bullet�̕��̃N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <btBulletDynamicsCommon.h>
#include "Base/pch.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

using namespace DirectX;

/**
* @enum BULLET_TYPE
* ���̂̌`��
*/
enum BULLET_TYPE { BT_SPHRER, BT_BOX, NONE_BULLET_TYPE };

class btObject {
public:
	btObject(BULLET_TYPE type, SimpleMath::Vector3 pos, SimpleMath::Vector3 scale, float rotZ, float mass);
	virtual ~btObject();

	void SetTransform(SimpleMath::Vector3 pos, SimpleMath::Vector3 rotate);
	void Moving(SimpleMath::Vector3 power);
	void LimitSpeed();

	/**
	* @brief ���̂�RigidBody��Ԃ�
	* @return RigitBody
	*/
	inline btRigidBody* Get_RigidBody() const { return bt_body_; };

	/**
	* @brief ���̂̒��S���W��Ԃ�
	* @return ���S���W
	*/
	inline SimpleMath::Vector2 GetCenterOfMassPosition() {
		const SimpleMath::Vector3 pos = (XMFLOAT3)bt_body_->getCenterOfMassPosition();
		return SimpleMath::Vector2(pos.x, pos.y);
	}

	/**
	* @brief �������Z�̈��������w�肷��
	* @param newState ���
	*/
	inline void SetActivationState(int newState) { bt_body_->setActivationState(newState); }

	/**
	* @brief ���W�E��]��ݒ肷��
	* @param position ���W
	* @param rotate ��]
	*/
	inline void SetCenterOfMassTransform(SimpleMath::Vector3 position, SimpleMath::Vector3 rotate) {
		btTransform transform = btTransform(*(btQuaternion*)&rotate, *(btVector3*)&position);
		bt_body_->setCenterOfMassTransform(transform);
	}

	/**
	* @brief �w�肵�������ɗ͂�������
	* @param forward ����
	*/
	inline void SetLinerVelocity(SimpleMath::Vector3 forward) { bt_body_->setLinearVelocity(*(btVector3*)&forward); }

	/**
	* @brief �����������~������
	*/
	inline void ResetVelocity() {
		btVector3 _vec(0.0f, 0.0f, 0.0f);
		bt_body_->setLinearVelocity(_vec);
		bt_body_->setAngularVelocity(_vec);
	}

private:
	////! ���̌`��
	//btCollisionShape*		bt_collision_;
	//
	////! �ʒu�E�p��
	//btDefaultMotionState*	bt_state_;

	//! ���̃I�u�W�F�N�g
	btRigidBody*			bt_body_;
};