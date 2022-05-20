/**
 * @file Choices.h
 * @brief �I���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_SoundPlayer/SoundPlayer.h"

class Choices {
public:
	Choices();
	virtual ~Choices() { delete se_choice_; };

	void Initialize();
	void Update(int choices, bool low, bool high);

	/**
	 * @brief ���ݑI�����Ă���ԍ���Ԃ�
	 * @return �I�����Ă���ԍ�
	*/
	int SelectNum() const { return isSelected; };

	/**
	 * @brief ���̓��͂��󂯕t������悤�ɂ���
	 * @param on ���̑I�����\���̐^�U
	*/
	void NextSelectOn(const bool on) { putCount_ = (int)on; }

private:
	//! ���͎���SE
	SoundPlayer* se_choice_;
	
	//! ���ݑI�����Ă���ԍ�
	int isSelected;

	//! ���͉�
	int putCount_;
};