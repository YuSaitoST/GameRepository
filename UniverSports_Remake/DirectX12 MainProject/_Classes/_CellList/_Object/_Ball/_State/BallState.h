#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

enum B_STATE { STANDBY, FLOATING, CAUTCH, SHOT, GOAL, NONE_STATE };
class ObjBall;

class BallState {
public:
	BallState() {}
	virtual ~BallState() {}

	virtual void Initialize() = 0;
	virtual void Update(ObjBall* ball) = 0;

	virtual void SetPosition(SimpleMath::Vector2 pos)	  { position_ = pos; }
	virtual void SetForward (SimpleMath::Vector2 forward) { forward_  = forward; }

	virtual SimpleMath::Vector2 GetPosition	() const { return position_; }
	virtual SimpleMath::Vector2 GetForward	() const { return forward_; }
	virtual B_STATE				GetMyState	() const { return myState_; }

protected:
	SimpleMath::Vector2 position_;
	SimpleMath::Vector2 forward_;
	B_STATE myState_;
};