#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_CellList\_Object/_Player/_BehaviorTree/ActionBase.h"

using namespace DirectX::SimpleMath;

class ObjPlayer;

class ActMove : public ActionBase {
public:
	ActMove() {};
	virtual ~ActMove() {};

	virtual void Initialize(int id) {}
	virtual void LoadAssets() {}
	virtual void Update(const float deltaTime, Vector2 direction, ObjPlayer& player);
	virtual void Update(const float deltaTime, ObjPlayer& player);
	virtual void UIRender() {}

	virtual bool Think(ObjPlayer& player);

private:
	float GetVectorLenght(Vector2 v);  // í∑Ç≥
	float DotProduct(Vector2 v1, Vector2 v2);  // ì‡êœ
	float AngleOf2Vector(Vector2 a, Vector2 b);  // Ç»Ç∑äpÉ∆

	Vector2 target_pos_new_;
	Vector2 target_pos_old_;
};