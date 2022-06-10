/**
 * @file CharaStrategy.h
 * @brief �v���C���[�̑���X�^�C�����N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/_ActMove/ActMove.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/_ActThrasher/ActThrasher.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/_ActShot/ActShot.h"

/**
* @enum OPERATE_TYPE
* �v���C���[�̑�����@
*/
enum OPERATE_TYPE { MANUAL, COMPUTER, NONE_OPERATE_TYPE };

//�O���錾
class ObjPlayer;

class CharaStrategy {
public:
	CharaStrategy() : rotate_x_(0.0f) { actList_ = { new ActThrasher(), new ActMove(), new ActShot() }; prevForward_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f); }
	virtual ~CharaStrategy() {}

	virtual void Initialize(int id, ObjPlayer* player) = 0;
	virtual void LoadAssets() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void UIRender() { for (ActionBase* act : actList_) act->UIRender(); }

	/**
	* @brief X���̊p�x��Ԃ�
	* @return X���̊p�x
	*/
	inline float GetRotateX() const { return rotate_x_; }

protected:
	/**
	* @brief �Ȃ߂炩�ɉ�]������
	* @param deltaTime �t���[�����Ƃ̌o�ߎ���
	* @param inputDirection ���͕���
	* @return X���̊p�x
	*/
	virtual float SeekRotateX(const float deltaTime, DirectX::XMFLOAT2 inputDirection) {
		DirectX::XMFLOAT3 _direction;
		_direction.x = inputDirection.x * std::sqrtf(1.0f - 0.5f * inputDirection.x * inputDirection.y);
		_direction.y = inputDirection.y * std::sqrtf(1.0f - 0.5f * inputDirection.x * inputDirection.y);
		_direction.z = 0;

		prevForward_ = Vector3::Lerp(prevForward_, _direction, deltaTime * 1.0f);
		return atan2f(prevForward_.y, prevForward_.x);
	}

	//! �v���C���[���g
	ObjPlayer* player_;

	//! �s���p�^�[���̃��X�g
	std::vector<ActionBase*> actList_;
	
	//! �ړ������̕␳�l
	DirectX::SimpleMath::Vector3 prevForward_;
	
	//! X���̊p�x
	float rotate_x_;
};