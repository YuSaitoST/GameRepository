#pragma once

#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StCautch : public BallState {
public:
	StCautch() = default;
	virtual ~StCautch() = default;

	virtual void Initialize();
	virtual void Update(ObjBall* ball);
};