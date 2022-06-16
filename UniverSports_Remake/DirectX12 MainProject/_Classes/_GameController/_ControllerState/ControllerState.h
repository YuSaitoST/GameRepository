/**
 * @file ControllerState.h
 * @brief ゲーム進行の状態基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

//前方宣言
class GameController;
class CountTimer;

class ControllerState {
public:
	ControllerState() {}
	virtual ~ControllerState() {}

	virtual void Initialize() = 0;
	virtual void LoadAsstes() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() = 0;

	virtual bool ChangeDrawing(GameController* controller) = 0;
	virtual CountTimer* GetTimer() = 0;
};