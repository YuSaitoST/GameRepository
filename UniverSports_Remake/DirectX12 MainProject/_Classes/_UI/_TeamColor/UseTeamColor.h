/**
 * @file UseTeamColor.h
 * @brief チームカラーのクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "TeamColor.h"
#include "Base/pch.h"
#include "Base/dxtk.h"
#include <array>

class UseTeamColor : public TeamColor {
public:
	UseTeamColor() {}
	virtual ~UseTeamColor() {}

	virtual void LoadAssets() override;
	virtual void Render(int playerID) override;

private:
	std::array<DX9::SPRITE, 2> sprite_;
};