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
	virtual ~IconAnimator();

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

	const int WIDTH				= 50;
	const int CEN_X_1			= 1280 * 0.5f - WIDTH - 40 * 3;
	const int CEN_X_2			= 1280 * 0.5f + WIDTH;
	const int CEN_Y_1			= 20;
	const int CEN_Y_2			= CEN_Y_1 + 40 + 10;

	const DirectX::XMFLOAT3 POS_LEFTICON[4] = {
		DirectX::XMFLOAT3(CEN_X_1,CEN_Y_1,0.0f),
		DirectX::XMFLOAT3(CEN_X_2,CEN_Y_1,0.0f),
		DirectX::XMFLOAT3(CEN_X_1,CEN_Y_2,0.0f),
		DirectX::XMFLOAT3(CEN_X_2,CEN_Y_2,0.0f)
	};

	//! �A�C�R��
	CharaIcon* icon_[4];
	
	//! �\�����Ԃ̃^�C�}�[
	CountTimer* display_time_;
	
	//! �摜�̃��l
	float alpha_;
	
	//! �\�����
	static bool display_;
};