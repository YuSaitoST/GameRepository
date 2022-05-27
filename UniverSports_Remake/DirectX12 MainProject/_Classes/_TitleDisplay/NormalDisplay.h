/**
 * @file NormalDisplay.h
 * @brief �^�C�g���̒ʏ��ʕ\���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "DisplayBase.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"
#include "_Classes/_UI/_Cursor/Cursor.h"
#include "_Classes/_UI/_SelectArrows/SelectArrows.h"
#include "_Classes/_UI/_Choices/Choices.h"
#include "_Classes/_UI/_SelectText/TextBase.h"
#include "_Classes/_UI/_SelectText/TextUI.h"
#include "_Classes/_UI/_OperateUI/OperateUI.h"
#include "_Classes/_UI/_BlackOut/BlackOut.h"

class NormalDisplay final : public DisplayBase {
public:
	NormalDisplay();
	virtual ~NormalDisplay();

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual NextScene Update(const float deltaTime) override;
	virtual void Render() override;
	virtual void Reset() override;
	virtual bool IsChange() override;

private:
	static const int	CHOICES				= 2;						// �c�̑I������
	static const int	MODE				= 3;						// ���[�h�̐�
	const float			SPEED_FADE[3]		= { 127.5f, 510.0f, 0.0f };	// �V�[���ڍs�̃t�F�[�h���x(2s, 0.5s�A0.0s)
	const float			UI_TEXT_Y[CHOICES]	= { 460.0f, 560.0f };		// �c��UI��Y���W
	const float			SPEED_ALPHA			= 127.5f;					// UI�̃t�F�[�h���x
	const float			ARROW_POS_R_X		= 917.5f;					// �E���X���W
	const float			ARROW_POS_L_X		= 328.5f;					// �����X���W
	const float			ARROW_POS_Y			= 455.0f;					// ���Y���W
	const float			TEXT_POS_X			= 640.0f;					// ���[�h�e�L�X�gX���W

private:
	SoundPlayer*	se_decision_;	//! ����SE
	CountTimer*		time_start_;	//! �^�C�g�����S���\�������܂ł̌v��
	CountTimer*		time_demo_;		//! �f���v���C�Đ��܂ł̃^�C�}�[
	Cursor*			cursor_;		//! �J�[�\��
	SelectArrows*	ui_arrows_;		//! ���[�h�I���̖��A�j���[�V����
	Choices*		mode_choices_;	//! ���[�h�I������
	OperateUI*		operate_;		//! �������
	BlackOut*		blackOut_;		//! �u���b�N�A�E�g

	TextBase* text_;								//! �I�������N���X
	TextUI nowText_[CHOICES][MODE];					//! �I�����z��

	float ui_alpha_;  //! UI�̃��l
};