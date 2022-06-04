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
	virtual ~IconAnimator() {}

	IconAnimator(IconAnimator&&) = delete;
	IconAnimator& operator= (IconAnimator&&) = delete;

	IconAnimator(IconAnimator const&) = delete;
	IconAnimator& operator= (IconAnimator const&) = delete;

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

	//! アイコン
	std::unique_ptr<CharaIcon> icon_[4];
	
	//! 表示時間のタイマー
	std::unique_ptr<CountTimer> display_time_;
	
	//! 画像のα値
	float alpha_;
	
	//! 表示状態
	static bool display_;
};