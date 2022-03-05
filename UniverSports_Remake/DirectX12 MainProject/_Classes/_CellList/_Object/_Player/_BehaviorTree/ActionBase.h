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
	virtual void Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player) = 0;  // �s�����e(Manual�p)
	virtual void Update(const float deltaTime, ObjPlayer& player) = 0;  // �s�����e(Computer�p)

	virtual bool Think(ObjPlayer& player) = 0;  // �s���������l������

	SimpleMath::Vector2 GetDirection() { return direction_; };

protected:
	SimpleMath::Vector2 direction_;
};