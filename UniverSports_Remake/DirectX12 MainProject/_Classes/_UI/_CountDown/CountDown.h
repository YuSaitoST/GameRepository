/**
 * @file CountDown.h
 * @brief �J�n���J�E���g�_�E���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include"Base/pch.h"
#include"Base/dxtk.h"
#include"_Classes/_SoundPlayer/SoundPlayer.h"

class CountDownUI {
public:
	CountDownUI();
	virtual ~CountDownUI() {}

	CountDownUI(CountDownUI&&) = delete;
	CountDownUI& operator= (CountDownUI&&) = delete;

	CountDownUI(CountDownUI const&) = delete;
	CountDownUI& operator= (CountDownUI const&) = delete;

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, float nowCount);
	void Render(float count) const;

private:
	const float			CENTER_X = 88.0f;
	const float			CENTER_Y = 37.5f;
	const float			POS_X	 = 543.0f + CENTER_X;
	const float			POS_Y	 = 325.0f + CENTER_Y;

	//! �J�E���g�_�E��SE
	std::unique_ptr<SoundPlayer> se_count_;
	
	//! �J�E���g�_�E���摜
	DX9::SPRITE	sprite_[4];
	
	//! �摜�̃��l
	float alpha_;
	
	//! �摜�T�C�Y
	float scale_;

	//! SE�Đ��t���O
	bool soundPlay_;
};