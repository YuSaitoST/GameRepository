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
	const float			SPEED_FADE[3]		= { 127.5f, 510.0f, 0.0f };  // �V�[���ڍs�̃t�F�[�h���x(2s, 0.5s�A0.0s)
	const float			UI_FADE_STARTTIME	= 2.5f;					// �^�C�g���w�i�ɍ��킹��UI���t�F�[�h�C�������鎞��
	const float			DEMO_PLAYBACK		= 10.0f;				// DEMO�v���C�Đ��܂ł̎���
	const float			UI_TEXT_Y[2]		= { 460.0f, 560.0f };	// �c��UI��Y���W
	const float			SPEED_ALPHA			= 127.5f;				// UI�̃t�F�[�h���x
	const float			ARROW_POS_R_X		= 917.5f;				// �E���X���W
	const float			ARROW_POS_L_X		= 328.5f;				// �����X���W
	const float			ARROW_POS_Y			= 455.0f;				// ���Y���W
	const float			TEXT_POS_X			= 640.0f;				// ���[�h�e�L�X�gX���W
	static const int	MODE				= 2;					// ���[�h�̐�
	static const int	CHOICES				= 2;					// �c�̑I������


private:
	SoundPlayer*		se_decision_;
	CountTimer*			time_start_;
	CountTimer*			time_demo_;
	Cursor*				cursor_;
	SelectArrows*		ui_arrows_;
	Choices*			mode_choices_;
	TextBase*			text_;
	TextUI				nowText_[MODE][CHOICES];
	OperateUI*			operate_;
	BlackOut*			blackOut_;

	float				ui_alpha_;
};