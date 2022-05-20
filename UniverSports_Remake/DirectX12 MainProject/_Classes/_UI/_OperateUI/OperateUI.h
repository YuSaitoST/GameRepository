/**
 * @file OperateUI.h
 * @brief ��������N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_StateOpe/StateOpeBase.h"
#include "_StateOpe/_Open/OpeClose.h"
#include "_StateOpe/_Close/OpeOpen.h"

using namespace DirectX;

class OperateUI {
public:
	OperateUI();
	virtual ~OperateUI() = default;

	void Initialize();
	void LoadAsset();
	void Update(const float deltaTime);
	void Render() const;

	void isPut();

	/**
	* @brief ���݂̏�Ԃ�Ԃ�
	* @return �\�����
	*/
	int isState() const { return num_state_; };

	/**
	* @brief �\����Ԃ�Ԃ�
	* @return �\������Ă����true�@����Ă��Ȃ����false
	*/
	bool isDisplayed() const { return isDisplay_; };

private:

	/**
	* @brief �A�j���[�V�������I���ɂ���
	*/
	void AnimateOn() { state_ = &st_open_; };

	/**
	* @brief �A�j���[�V�������I�t�ɂ���
	*/
	void AnimateOff() { state_ = &st_close_; };

private:
	const int OPERATE_COUNT = 2;

	//!���������Ԋ��N���X
	OP_StateBase*	state_;

	//! ���������\����������
	OpeOpen			st_open_;

	//! ��������������
	OpeClose		st_close_;

	//! �L�[�{�[�h��������摜
	DX9::SPRITE sp_keybord_;

	//! �Q�[���p�b�h��������摜
	DX9::SPRITE sp_gamepad_;

	//! �L�[�{�[�h��������摜�̍��W
	SimpleMath::Vector3 pos_key_;

	//! �Q�[���p�b�h��������摜�̍��W
	SimpleMath::Vector3 pos_pad_;

	//! ���݂̏��
	int num_state_;

	//! �\�����
	bool isDisplay_;
};