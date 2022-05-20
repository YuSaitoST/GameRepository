/**
 * @file IconAnimator.h
 * @brief 残機アイコンのアニメーションクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
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
	* @brief 表示状態を返す
	* @return 表示状態
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

	//! アイコン
	CharaIcon* icon_[4];
	
	//! 表示時間のタイマー
	CountTimer* display_time_;
	
	//! 画像のα値
	float alpha_;
	
	//! 表示状態
	static bool display_;
};