/**
 * @file BlackOut.h
 * @brief ブラックアウトクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */
#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

using namespace DirectX;

/**
 * @enum BLACKOUT_MODE
 * 開始状態
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
	//! 開始状態
	BLACKOUT_MODE	mode_;
	
	//! 画像
	DX9::SPRITE		sprite_;
	
	//! α値
	float			alpha_;
};