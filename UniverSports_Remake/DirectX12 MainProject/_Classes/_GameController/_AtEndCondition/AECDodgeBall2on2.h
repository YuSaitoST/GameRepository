/**
 * @file AECDodgeBall2on2.h
 * @brief ドッジボール2on2モードの終了条件クラス
 * @author 齋藤優宇
 * @date 2021/06/04
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "AtEndCondition.h"
#include "DontDestroyOnLoad.h"

class AECDodgeBall2on2 : public AtEndCondition {
public:
	AECDodgeBall2on2() {}
	virtual ~AECDodgeBall2on2() {}

	/**
	* @brief ゲームが終了したかを返す
	* @return ゲームの終了状態
	*/
	virtual bool IsFined() override { return DontDestroy->Survivor_.RemainingOfTeam() <= 1; }
};