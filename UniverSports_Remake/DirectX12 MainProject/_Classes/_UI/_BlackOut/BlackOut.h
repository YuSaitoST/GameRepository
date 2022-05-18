/**
 * @file BlackOut.h
 * @brief �u���b�N�A�E�g�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */
#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

using namespace DirectX;

/**
 * @enum BLACKOUT_MODE
 * �J�n���
 */
enum BLACKOUT_MODE { FADE_IN, FADE_OUT, NONE_ANIMATION };

class BlackOut {
public:
	BlackOut();
	virtual ~BlackOut() {};

	void Initialize(BLACKOUT_MODE state);
	void LoadAsset();
	void Update(const float deltaTime);
	void Render();

	bool isDone();

private:
	const float		RGBA_MAX		= 255.0f;
	const float		TIME_FADEIN		= RGBA_MAX / 5.0f;
	const float		TIME_FADEOUT	= RGBA_MAX / 0.5f;

private:
	//! �J�n���
	BLACKOUT_MODE	mode_;
	
	//! �摜
	DX9::SPRITE		sprite_;
	
	//! ���l
	float			alpha_;
};