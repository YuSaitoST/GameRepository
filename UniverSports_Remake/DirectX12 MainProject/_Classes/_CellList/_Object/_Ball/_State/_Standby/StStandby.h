#pragma once

#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StStandby : public BallState {
public:
	StStandby() {}
	virtual ~StStandby() {}

	virtual void Initialize();
	virtual void Update(ObjBall* ball);
};