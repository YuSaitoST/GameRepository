#pragma once

#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StShot : public BallState {
public:
	StShot() : pos_z_(0.0f) {};
	virtual ~StShot() {}

	virtual void Initialize();
	virtual void Update(ObjBall* ball);

private:
	float pos_z_;
};