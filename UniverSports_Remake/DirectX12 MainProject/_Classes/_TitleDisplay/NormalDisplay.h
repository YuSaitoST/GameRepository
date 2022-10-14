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
#include "_Classes/_UI/_ChoicesText/ChoicesText.h"
#include "_Classes/_UI/_OperateUI/OperateUI.h"
#include "_Classes/_UI/_BlackOut/BlackOut.h"
#include "_Classes/_MoviePlayer/MoviePlayer.h"

class NormalDisplay final : public DisplayBase {
public:
	NormalDisplay();
	virtual ~NormalDisplay() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual NextScene Update(const float deltaTime) override;
	virtual void Render() override;
	virtual void Reset() override;
	virtual DISPLAYMODE IsChange() override;
	virtual void ReDisplayInitialize() override;

private:
	static const int	CHOICES				= 2;						// 縦の選択肢数
	static const int	MODE				= 3;						// モードの数
	const int			COUNT_MAX[CHOICES]	= { 3, 2 };
	const float			SPEED_FADE[3]		= { 127.5f, 510.0f, 0.0f };	// シーン移行のフェード速度(2s, 0.5s、0.0s)
	const float			SPEED_ALPHA			= 127.5f;					// UIのフェード速度
	const float			CURSOR_POS_X		= 360.0f;					// カーソルのX座標
	const float			CURSOR_POS_Y		= 415.0f;					// カーソルのY座標

private:
	std::unique_ptr<SoundPlayer>	se_decision_;				//! 決定SE
	std::unique_ptr<CountTimer>		time_start_;				//! タイトルロゴが表示されるまでの計測
	std::unique_ptr<CountTimer>		time_demo_;					//! デモプレイ再生までのタイマー
	std::unique_ptr<Cursor>			cursor_;					//! カーソル
	std::unique_ptr<SelectArrows>	ui_arrows_;					//! モード選択の矢印アニメーション
	std::unique_ptr<ChoicesText>	ui_text_[CHOICES];			//! 選択肢配列
	std::unique_ptr<Choices>		mode_choices_;				//! モード選択処理
	std::unique_ptr<OperateUI>		operate_;					//! 操作説明
	std::unique_ptr<BlackOut>		blackOut_;					//! ブラックアウト
	std::unique_ptr<MoviePlayer>	movie_;						//! 背景動画

	float	ui_alpha_;				//! UIのα値
	float	pos_y_arrows_[CHOICES];	//! 矢印の座標リスト
	int		selectID_[CHOICES];		//! 選択されている番号
	int		isOtherSelect_;			//! 設定画面へ遷移するフラグ
};