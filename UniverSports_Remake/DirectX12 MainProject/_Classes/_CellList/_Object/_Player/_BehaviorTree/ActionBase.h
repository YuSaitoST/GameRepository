/**
 * @file ActionBase.h
 * @brief �v���C���[�̍s�����N���X
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
* @enum BEHAVIOR
* �s���p�^�[��
*/
enum BEHAVIOR { IS_MOVE, IS_SHOT, IS_ACCEL, IS_NONE };

//�O���錾
class ObjPlayer;

class ActionBase {
public:
	ActionBase() {};
	virtual ~ActionBase() {};

	virtual void Initialize(int id) = 0;
	virtual void LoadAssets() = 0;
	virtual void Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player) = 0;  // �s�����e(Manual�p)
	virtual void Update(const float deltaTime, ObjPlayer& player) = 0;  // �s�����e(Computer�p)
	virtual void UIRender() = 0;

	virtual bool Think(ObjPlayer& player) = 0;  // �s���������l������

	/**
	* @brief ���ʕ�����Ԃ�
	* @return ���ʕ���
	*/
	SimpleMath::Vector2 GetDirection() { return direction_; };

protected:
	//! ���ʃx�N�g��
	SimpleMath::Vector2 direction_;
};