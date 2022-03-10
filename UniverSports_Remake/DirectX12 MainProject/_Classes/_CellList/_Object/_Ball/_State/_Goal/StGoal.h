#pragma once

#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StGoal : public BallState {
public:
	StGoal() = default;
	virtual ~StGoal() = default;

	virtual void Initialize();
	virtual void Update(ObjBall* ball);
};