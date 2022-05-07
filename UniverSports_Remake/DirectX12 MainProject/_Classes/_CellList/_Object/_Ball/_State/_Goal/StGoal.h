#pragma once

#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StGoal : public BallState {
public:
	StGoal() {}
	virtual ~StGoal() {}

	virtual void Initialize();
	virtual void Update(ObjBall* ball);
};