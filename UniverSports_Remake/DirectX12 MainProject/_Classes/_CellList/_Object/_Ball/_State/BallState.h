/**
 * @file BallState.h
 * @brief �{�[���̏�Ԋ��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

/**
* @enum B_STATE
* �{�[���̏��
*/
enum class B_STATE { STANDBY, FLOATING, CAUTCH, SHOT, GOAL, NONE_STATE };

//�O���錾
class ObjBall;

class BallState {
public:
	BallState() : myState_(B_STATE::NONE_STATE) {}
	virtual ~BallState() {}

	virtual void Initialize() = 0;
	virtual void Update(ObjBall* ball) = 0;
	
	/**
	* @brief ��Ԃ�Ԃ�
	* @return ���
	*/
	inline B_STATE GetMyState () const { return myState_; }

protected:
	SimpleMath::Vector2 position_;	//! ���W
	B_STATE myState_;				//! ���
};