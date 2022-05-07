#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

enum B_STATE { STANDBY, FLOATING, CAUTCH, SHOT, GOAL, NONE_STATE };

// ëOï˚êÈåæ
class ObjBall;

class BallState {
public:
	BallState() : myState_(B_STATE::NONE_STATE) {}
	virtual ~BallState() {}

	virtual void Initialize() = 0;
	virtual void Update(ObjBall* ball) = 0;

	virtual void SetPosition(SimpleMath::Vector2 pos)	  { position_ = pos; };
	virtual void SetForward (SimpleMath::Vector2 forward) { forward_  = forward; };

	virtual SimpleMath::Vector2 GetPosition	() const { return position_; };
	virtual SimpleMath::Vector2 GetForward	() const { return forward_; };

	B_STATE MyState() const { return myState_; }

protected:
	SimpleMath::Vector2 position_;
	SimpleMath::Vector2 forward_;
	B_STATE myState_;
};