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
	virtual ~NormalDisplay() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual NextScene Update(const float deltaTime) override;
	virtual void Render() override;
	virtual void Reset() override;
	virtual bool IsChange() override;

private:
	static const int	CHOICES				= 2;						// 縦の選択肢数
	static const int	MODE				= 2;						// モードの数
	const float			SPEED_FADE[3]		= { 127.5f, 510.0f, 0.0f };	// シーン移行のフェード速度(2s, 0.5s、0.0s)
	const float			SPEED_ALPHA			= 127.5f;					// UIのフェード速度

private:
	std::unique_ptr<SoundPlayer>	se_decision_;	//! 決定SE
	std::unique_ptr<CountTimer>		time_start_;	//! タイトルロゴが表示されるまでの計測
	std::unique_ptr<CountTimer>		time_demo_;		//! デモプレイ再生までのタイマー
	std::unique_ptr<Cursor>			cursor_;		//! カーソル
	std::unique_ptr<SelectArrows>	ui_arrows_;		//! モード選択の矢印アニメーション
	std::unique_ptr<Choices>		mode_choices_;	//! モード選択処理
	std::unique_ptr<OperateUI>		operate_;		//! 操作説明
	std::unique_ptr<BlackOut>		blackOut_;		//! ブラックアウト

	TextBase* text_;								//! 選択肢基底クラス
	TextUI nowText_[CHOICES][MODE];					//! 選択肢配列

	float ui_alpha_;  //! UIのα値
};