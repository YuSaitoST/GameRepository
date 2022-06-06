/**
 * @file StGoal.h
 * @brief ボールのゴール状態クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StGoal : public BallState {
public:
	StGoal() {}
	virtual ~StGoal() {}

	virtual void Initialize();
	virtual void Update(ObjBall* ball);
};