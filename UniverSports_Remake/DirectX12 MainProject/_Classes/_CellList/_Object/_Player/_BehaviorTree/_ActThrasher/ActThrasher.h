/**
 * @file ActThrasher.h
 * @brief 加速行動クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_CellList\_Object/_Player/_BehaviorTree/ActionBase.h"
#include "_EffThrasher/EffThrasher.h"
#include "_Gauge/Gauge.h"

using namespace DirectX;

//前方宣言
class ObjPlayer;

class ActThrasher : public ActionBase {
public:
	ActThrasher();
	virtual ~ActThrasher();

	virtual void Initialize(int id);
	virtual void LoadAssets();
	virtual void Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player);
	virtual void Update(const float deltaTime, ObjPlayer& player);
	virtual void UIRender();

	virtual bool Think(ObjPlayer& player);

private:
	//! スラスターエフェクト
	EffThrasher* effect_;

	//! スラスターゲージ
	Gauge* gauge_;
};