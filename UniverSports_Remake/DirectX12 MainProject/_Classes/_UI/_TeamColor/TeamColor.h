/**
 * @file TeamColor.h
 * @brief チームカラーの基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

class TeamColor {
public:
	TeamColor() {}
	virtual ~TeamColor() {}

	virtual void Initialize() = 0;
	virtual void LoadAssets() = 0;
	virtual void Render(int playerID) = 0;
};