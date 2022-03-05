#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_CellList\_Object/_Player/_BehaviorTree/ActionBase.h"
#include "_EffThrasher/EffThrasher.h"

using namespace DirectX;

class ObjPlayer;

class ActThrasher : public ActionBase {
public:
	ActThrasher();
	virtual ~ActThrasher();

	virtual void Initialize(int id);
	virtual void LoadAssets();
	virtual void Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player);
	virtual void Update(const float deltaTime, ObjPlayer& player);

	virtual bool Think(ObjPlayer& player);

private:
	EffThrasher* effect_;
};