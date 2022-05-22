/**
 * @file ComputerChara.h
 * @brief コンピューター操作クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Player/_Strategy/CharaStrategy.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/ActionBase.h"

class ComputerChara final : public CharaStrategy {
public:
	ComputerChara() {};
	virtual ~ComputerChara() {};

	virtual void Initialize(int id, ObjPlayer* player) override;
	virtual void LoadAssets() override;
	virtual void Update(const float deltaTime) override;
};