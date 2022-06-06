/**
 * @file StCautch.h
 * @brief ボールのキャッチ状態クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StCautch : public BallState {
public:
	StCautch() {}
	virtual ~StCautch() {}

	virtual void Initialize();
	virtual void Update(ObjBall* ball);
};