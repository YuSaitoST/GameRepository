/**
 * @file DrawingByMode.h
 * @brief モードに依存するリザルト画面描画の基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_FileNames/FileNames.h"

class DrawingByMode {
public:
	DrawingByMode();
	virtual ~DrawingByMode() {}

	virtual void Initialize() = 0;
	virtual void LoadAssets() = 0;
	virtual void Render() = 0;

protected:
	virtual void CommonCalculation(int* winPlayerID);
	virtual void CommonLoadAssets();
	virtual void CommonDrawing();
	
	std::vector<DX9::SPRITE>	sp_winPlayer_;
	DX9::SPRITE					sp_playerName_;
	DX9::SPRITE					sp_number_;

	int							maxScore_;
	int							player_rect_x[2];
	int							oneDigit_x;
	int							twoDigit_x;
};