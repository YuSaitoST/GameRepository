/**
 * @file IconAnimator.h
 * @brief �c�@�A�C�R���̃A�j���[�V�����N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "CharaIcon.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

class IconAnimator {
public:
	IconAnimator();
	virtual ~IconAnimator() {}

	IconAnimator(IconAnimator&&) = delete;
	IconAnimator& operator= (IconAnimator&&) = delete;

	IconAnimator(IconAnimator const&) = delete;
	IconAnimator& operator= (IconAnimator const&) = delete;

	void LoadAssets();
	void Update(const float deltaTime);
	void Render(const int lifeCount, int index);

	/**
	* @brief �\����Ԃ�Ԃ�
	* @return �\�����
	*/
	static void DisplayOn() { display_ = true; }

private:
	const float SPEED_FADEIN	= 255.0f;
	const float SPEED_FADEOUT	= 127.5f;

	//! �A�C�R��
	std::unique_ptr<CharaIcon> icon_[4];
	
	//! �\�����Ԃ̃^�C�}�[
	std::unique_ptr<CountTimer> display_time_;
	
	//! �摜�̃��l
	float alpha_;
	
	//! �\�����
	static bool display_;
};