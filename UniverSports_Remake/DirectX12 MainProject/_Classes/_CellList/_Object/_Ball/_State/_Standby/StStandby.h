/**
 * @file StStandby.h
 * @brief ボールの待機状態クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StStandby : public BallState {
public:
	StStandby() {}
	virtual ~StStandby() {}

	virtual void Initialize();
	virtual void Update(ObjBall* ball);
};