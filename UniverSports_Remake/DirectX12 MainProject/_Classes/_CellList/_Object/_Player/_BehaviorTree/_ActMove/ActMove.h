#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_CellList\_Object/_Player/_BehaviorTree/ActionBase.h"

using namespace DirectX;

class ObjPlayer;

class ActMove : public ActionBase {
public:
	ActMove() {};
	virtual ~ActMove() {};

	virtual void Initialize(int id);
	virtual void LoadAssets();
	virtual void Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player);
	virtual void Update(const float deltaTime, ObjPlayer& player);
	virtual void UIRender() {}

	virtual bool Think(ObjPlayer& player);
};