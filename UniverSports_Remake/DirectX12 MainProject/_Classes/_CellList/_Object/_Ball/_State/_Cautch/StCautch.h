#pragma once

#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StCautch : public BallState {
public:
	StCautch() {}
	virtual ~StCautch() {}

	virtual void Initialize();
	virtual void Update(ObjBall* ball);

private:
	const float Z_MIN = -8.0f;
};