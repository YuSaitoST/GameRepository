#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

enum BEHAVIOR {
	IS_MOVE,
	IS_SHOT,
	IS_ACCEL,
	IS_NONE
};

class ObjPlayer;

class ActionBase {
public:
	ActionBase() {};
	virtual ~ActionBase() {};

	virtual void Initialize(int id) = 0;
	virtual void LoadAssets() = 0;
	virtual void Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player) = 0;  // 行動内容(Manual用)
	virtual void Update(const float deltaTime, ObjPlayer& player) = 0;  // 行動内容(Computer用)

	virtual bool Think(ObjPlayer& player) = 0;  // 行動条件を考慮する

	SimpleMath::Vector2 GetDirection() { return direction_; };

protected:
	SimpleMath::Vector2 direction_;
};