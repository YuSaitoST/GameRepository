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
	virtual ~Choices() {};

	Choices(Choices&&) = delete;
	Choices& operator= (Choices&&) = delete;

	Choices(Choices const&) = delete;
	Choices& operator= (Choices const&) = delete;

	void Initialize();
	void Update(int choices, bool low, bool high);

	/**
	 * @brief ���ݑI�����Ă���ԍ���Ԃ�
	 * @return �I�����Ă���ԍ�
	*/
	inline int SelectNum() const { return isSelected_; };

	/*
	* @brifef �I�������w�肷��
	* @param �I���������ԍ�
	*/
	inline void SetSelectNum(int number) { isSelected_ = number; }

	/**
	 * @brief ���̓��͂��󂯕t������悤�ɂ���
	 * @param on ���̑I�����\���̐^�U
	*/
	inline void NextSelectOn(const bool on) { putCount_ = (int)on; }

private:
	//! ���͎���SE
	std::unique_ptr<SoundPlayer> se_choice_;
	
	//! ���ݑI�����Ă���ԍ�
	int isSelected_;

	//! ���͉�
	int putCount_;
};