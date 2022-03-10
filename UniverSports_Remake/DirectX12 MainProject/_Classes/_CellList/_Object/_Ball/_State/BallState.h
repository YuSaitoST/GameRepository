#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjBall;

class BallState {
public:
	BallState() = default;
	virtual ~BallState() = default;

	virtual void Initialize() = 0;
	virtual void Update(ObjBall* ball) = 0;

	virtual void SetPosition(SimpleMath::Vector2 pos)	  { position_ = pos; };
	virtual void SetForward (SimpleMath::Vector2 forward) { forward_  = forward; };

	virtual SimpleMath::Vector2 GetPosition	() const { return position_; };
	virtual SimpleMath::Vector2 GetForward	() const { return forward_; };

protected:
	SimpleMath::Vector2 position_;
	SimpleMath::Vector2 forward_;
};