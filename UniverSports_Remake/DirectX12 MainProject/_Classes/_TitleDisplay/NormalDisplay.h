/**
 * @file NormalDisplay.h
 * @brief タイトルの通常画面表示クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "DisplayBase.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"
#include "_Classes/_UI/_Cursor/Cursor.h"
#include "_Classes/_UI/_SelectArrows/SelectArrows.h"
#include "_Classes/_UI/_Choices/Choices.h"
#include "_Classes/_UI/_SelectText/TextBase.h"
#include "_Classes/_UI/_SelectText/TextUI.h"
#include "_Classes/_UI/_OperateUI/OperateUI.h"
#include "_Classes/_UI/_BlackOut/BlackOut.h"

class NormalDisplay final : public DisplayBase {
public:
	NormalDisplay();
	virtual ~NormalDisplay();

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual NextScene Update(const float deltaTime) override;
	virtual void Render() override;
	virtual void Reset() override;
	virtual bool IsChange() override;

private:
	static const int	CHOICES				= 2;						// 縦の選択肢数
	static const int	MODE				= 3;						// モードの数
	const float			SPEED_FADE[3]		= { 127.5f, 510.0f, 0.0f };	// シーン移行のフェード速度(2s, 0.5s、0.0s)
	const float			UI_TEXT_Y[CHOICES]	= { 460.0f, 560.0f };		// 縦のUIのY座標
	const float			SPEED_ALPHA			= 127.5f;					// UIのフェード速度
	const float			ARROW_POS_R_X		= 917.5f;					// 右矢印X座標
	const float			ARROW_POS_L_X		= 328.5f;					// 左矢印X座標
	const float			ARROW_POS_Y			= 455.0f;					// 矢印Y座標
	const float			TEXT_POS_X			= 640.0f;					// モードテキストX座標

private:
	SoundPlayer*	se_decision_;	//! 決定SE
	CountTimer*		time_start_;	//! タイトルロゴが表示されるまでの計測
	CountTimer*		time_demo_;		//! デモプレイ再生までのタイマー
	Cursor*			cursor_;		//! カーソル
	SelectArrows*	ui_arrows_;		//! モード選択の矢印アニメーション
	Choices*		mode_choices_;	//! モード選択処理
	OperateUI*		operate_;		//! 操作説明
	BlackOut*		blackOut_;		//! ブラックアウト

	TextBase* text_;								//! 選択肢基底クラス
	TextUI nowText_[CHOICES][MODE];					//! 選択肢配列

	float ui_alpha_;  //! UIのα値
};