/**
 * @file GamePadEvent.h
 * @brief ゲームパッドの単発入力クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "GamePadBase.h"

class GamePadEvent final : public GamePadBase {
public:
	GamePadEvent() {}
	virtual ~GamePadEvent() {}

	virtual void Accepts(int index) override;
};