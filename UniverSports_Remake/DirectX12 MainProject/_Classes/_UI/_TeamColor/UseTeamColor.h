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
#include <random>

class UseTeamColor : public TeamColor {
public:
	UseTeamColor();
	virtual ~UseTeamColor() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual void Render(int playerID) override;

private:
	void GiveTeamID(int myID);

	std::mt19937						randomEngine_;
	std::uniform_int_distribution<>		newTeamID_;
	std::array<DX9::SPRITE, 2>			sprite_;		//! チームカラー画像
};