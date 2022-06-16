/**
 * @file EffectBase.h
 * @brief エフェクトの基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "AtEndCondition.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

class AECHandBall : public AtEndCondition {
public:
	AECHandBall() {}
	virtual ~AECHandBall() {}

	/**
	* @brief ゲームが終了したかを返す
	* @return ゲームの終了状態
	*/
	virtual bool IsFined(CountTimer* timer) override { return (timer != nullptr) ? timer->TimeOut() : false; }
};