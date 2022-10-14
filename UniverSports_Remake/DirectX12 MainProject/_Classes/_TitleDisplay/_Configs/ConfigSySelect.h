/**
 * @file ConfigSySelect.h
 * @brief プレイヤー選択クラス
 * @author 齋藤優宇
 * @date 2021/09/17
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "ConfigState.h"
#include "_Classes/_UI/_SelectArrows/SelectArrows.h"
#include "_Classes/_UI/_Choices/Choices.h"

class ConfigSySelect : public ConfigState {
public:
	ConfigSySelect();
	virtual ~ConfigSySelect() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual void Update(const float deltaTime, ConfigDisplay* conDisplay) override;
	virtual void Render(DX9::SPRITEFONT font) override;

private:
	const int CURSOR_MOVE_Y		= 160;
	const int CURSOR_RIGHT_X	= 750;
	const int CURSOR_LEFT_X		= 400;

private:
	std::unique_ptr<SelectArrows>	ui_arrows_;
	std::unique_ptr<Choices>		systemChoices_;
	float							arrow_pos_y_;
};