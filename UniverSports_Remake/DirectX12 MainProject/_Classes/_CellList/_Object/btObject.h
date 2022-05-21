/**
 * @file btObject.h
 * @brief Bulletの物体クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <btBulletDynamicsCommon.h>
#include "Base/pch.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

using namespace DirectX;

/**
* @enum BULLET_TYPE
* 物体の形状
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
	* @brief 物体のRigidBodyを返す
	* @return RigitBody
	*/
	inline btRigidBody* Get_RigidBody() const { return bt_body_; };

	/**
	* @brief 物体の中心座標を返す
	* @return 中心座標
	*/
	inline SimpleMath::Vector2 GetCenterOfMassPosition() {
		const SimpleMath::Vector3 pos = (XMFLOAT3)bt_body_->getCenterOfMassPosition();
		return SimpleMath::Vector2(pos.x, pos.y);
	}

	/**
	* @brief 物理演算の扱い方を指定する
	* @param newState 状態
	*/
	inline void SetActivationState(int newState) { bt_body_->setActivationState(newState); }

	/**
	* @brief 座標・回転を設定する
	* @param position 座標
	* @param rotate 回転
	*/
	inline void SetCenterOfMassTransform(SimpleMath::Vector3 position, SimpleMath::Vector3 rotate) {
		btTransform transform = btTransform(*(btQuaternion*)&rotate, *(btVector3*)&position);
		bt_body_->setCenterOfMassTransform(transform);
	}

	/**
	* @brief 指定した方向に力を加える
	* @param forward 方向
	*/
	inline void SetLinerVelocity(SimpleMath::Vector3 forward) { bt_body_->setLinearVelocity(*(btVector3*)&forward); }

	/**
	* @brief 物理挙動を停止させる
	*/
	inline void ResetVelocity() {
		btVector3 _vec(0.0f, 0.0f, 0.0f);
		bt_body_->setLinearVelocity(_vec);
		bt_body_->setAngularVelocity(_vec);
	}

private:
	////! 球体形状
	//btCollisionShape*		bt_collision_;
	//
	////! 位置・姿勢
	//btDefaultMotionState*	bt_state_;

	//! 剛体オブジェクト
	btRigidBody*			bt_body_;
};