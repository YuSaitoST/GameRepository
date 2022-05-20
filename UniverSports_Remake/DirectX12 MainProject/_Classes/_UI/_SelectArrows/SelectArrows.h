/**
 * @file SelectArrows.h
 * @brief 選択時の左右矢印クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class SelectArrows {
public:
	SelectArrows();
	virtual ~SelectArrows() {};

	void Initialize(float x_right, float x_left, float y);
	void LoadAssets();
	void LoadAssets(DX9::SPRITE right, DX9::SPRITE left);
	bool Update(const int index);
	void Render(float alpha);

private:
	void Animations(float& scale);

	/**
	 * @brief サイズを一定値まで拡大する
	 * @param scale サイズ
	*/
	void GetBigger(float& scale) { scale = std::min(scale + SPEED_BIGGER, SCALE_MAX); }

	/**
	 * @brief サイズを一定値まで縮小する
	 * @param scale サイズ
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
	 * 入力状態
	*/
	enum INPUT_SELECT { AL_RIGHT, AL_LEFT, AL_NONE };

	//! 入力状態
	INPUT_SELECT input_;

	//! 右矢印の画像
	DX9::SPRITE sp_right_;
	
	//! 左矢印の画像
	DX9::SPRITE sp_left_;

	//! 右矢印のX座標
	float pos_right_x_;

	//! 左矢印のX座標
	float pos_left_x_;

	//! 矢印のY座標
	float pos_y_;

	//! 右矢印のサイズ
	float scale_right_;

	//! 左矢印のサイズ
	float scale_left_;

	//! 拡大の終了状態
	bool isFinBigger;

	//! 縮小の終了状態
	bool isFinSmaller;
};