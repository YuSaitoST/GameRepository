/**
 * @file ManualChara.h
 * @brief プレイヤー自身が操作するクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Player/_Strategy/CharaStrategy.h"

class ManualChara final : public CharaStrategy {
public:
	ManualChara() {};
	virtual ~ManualChara() {};

	virtual void Initialize(int id, ObjPlayer* player) override;
	virtual void LoadAssets() override;
	virtual void Update(const float deltaTime) override;
};