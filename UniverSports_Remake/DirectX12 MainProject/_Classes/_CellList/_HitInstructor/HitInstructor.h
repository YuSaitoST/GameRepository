#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class HitInstructor {
public:
	HitInstructor() {}
	virtual ~HitInstructor() {}

	static void BallCautch(const int playerID, const int ballID);
	static void BallShot(const int ballID, DirectX::SimpleMath::Vector2 forward);
	static void BallBreak(const int ballID);
};