/**
 * @file SelectArrows.h
 * @brief �I�����̍��E���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class SelectArrows {
public:
	SelectArrows();
	virtual ~SelectArrows() {};

	void Initialize(float x_right, float x_left);
	void LoadAssets();
	void LoadAssets(DX9::SPRITE right, DX9::SPRITE left);
	bool Update(const int index);
	void Render(float alpha, float posY);

private:
	void Animations(float& scale);

	/**
	 * @brief �T�C�Y�����l�܂Ŋg�傷��
	 * @param scale �T�C�Y
	*/
	void GetBigger(float& scale) { scale = std::min(scale + SPEED_BIGGER, SCALE_MAX); }

	/**
	 * @brief �T�C�Y�����l�܂ŏk������
	 * @param scale �T�C�Y
	*/
	void GetSmaller(float& scale) { scale = std::max(1.0f, scale - SPEED_SMALLER); }

private:
	const float RECT		= 12.5f;
	const float SCALE_MAX	= 1.5f;
	const float SPEED_BIGGER = 0.15f;
	const float SPEED_SMALLER = 0.1f;

private:
	/**
	 * @enum INPUT_SELECT
	 * ���͏��
	*/
	enum INPUT_SELECT { AL_RIGHT, AL_LEFT, AL_NONE };

	INPUT_SELECT	input_;			//! ���͏��

	DX9::SPRITE		sp_right_;		//! �E���̉摜
	DX9::SPRITE		sp_left_;		//! �����̉摜

	float			pos_right_x_;	//! �E����X���W
	float			pos_left_x_;	//! ������X���W
	float			scale_right_;	//! �E���̃T�C�Y
	float			scale_left_;	//! �����̃T�C�Y
	bool			isFinBigger;	//! �g��̏I�����
	bool			isFinSmaller;	//! �k���̏I�����
};