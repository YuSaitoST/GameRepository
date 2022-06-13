/**
 * @file UseTeamColor.h
 * @brief キャラクター未選択状態の描画クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "UserInputRender.h"

class UnSelectedRender : public UserInputRender {
public:
	UnSelectedRender() : sp_decision_(DX9::SPRITE{}) {}
	virtual ~UnSelectedRender() {}

	virtual void LoadAssets() override;
	virtual void Render(int playerID) override;

private:
	DX9::SPRITE sp_decision_;	//! 決定
};