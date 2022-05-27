/**
 * @file CountDown.h
 * @brief 開始時カウントダウンクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
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

	//! カウントダウンSE
	std::unique_ptr<SoundPlayer> se_count_;
	
	//! カウントダウン画像
	DX9::SPRITE	sprite_[4];
	
	//! 画像のα値
	float alpha_;
	
	//! 画像サイズ
	float scale_;

	//! SE再生フラグ
	bool soundPlay_;
};