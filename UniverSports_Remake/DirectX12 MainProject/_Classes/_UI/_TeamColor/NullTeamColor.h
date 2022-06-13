/**
 * @file NullTeamColor.h
 * @brief チームカラーのNullオブジェクトクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "TeamColor.h"

class NullTeamColor : public TeamColor {
public:
	NullTeamColor() {}
	virtual ~NullTeamColor() {}

	virtual void LoadAssets() override {}
	virtual void Render(int teamID) override {}
};