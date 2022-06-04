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
	virtual ~NormalDisplay() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual NextScene Update(const float deltaTime) override;
	virtual void Render() override;
	virtual void Reset() override;
	virtual bool IsChange() override;

private:
	static const int	CHOICES				= 2;						// �c�̑I������
	static const int	MODE				= 2;						// ���[�h�̐�
	const float			SPEED_FADE[3]		= { 127.5f, 510.0f, 0.0f };	// �V�[���ڍs�̃t�F�[�h���x(2s, 0.5s�A0.0s)
	const float			SPEED_ALPHA			= 127.5f;					// UI�̃t�F�[�h���x

private:
	std::unique_ptr<SoundPlayer>	se_decision_;	//! ����SE
	std::unique_ptr<CountTimer>		time_start_;	//! �^�C�g�����S���\�������܂ł̌v��
	std::unique_ptr<CountTimer>		time_demo_;		//! �f���v���C�Đ��܂ł̃^�C�}�[
	std::unique_ptr<Cursor>			cursor_;		//! �J�[�\��
	std::unique_ptr<SelectArrows>	ui_arrows_;		//! ���[�h�I���̖��A�j���[�V����
	std::unique_ptr<Choices>		mode_choices_;	//! ���[�h�I������
	std::unique_ptr<OperateUI>		operate_;		//! �������
	std::unique_ptr<BlackOut>		blackOut_;		//! �u���b�N�A�E�g

	TextBase* text_;								//! �I�������N���X
	TextUI nowText_[CHOICES][MODE];					//! �I�����z��

	float ui_alpha_;  //! UI�̃��l
};