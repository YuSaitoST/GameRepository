/**
 * @file UserInputRender.h
 * @brief キャラクター選択の入力状態基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class UserInputRender {
public:
	UserInputRender() {}
	virtual ~UserInputRender() {}

	virtual void LoadAssets() = 0;
	virtual void Render(int playerID) = 0;
};