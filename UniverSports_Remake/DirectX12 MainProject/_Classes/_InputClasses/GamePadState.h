#pragma once

#include "GamePadBase.h"

class GamePadState final : public GamePadBase {
public:
	GamePadState() : n_Lx_(0), n_Ly_(0), n_Rx_(0), n_Ry_(0), n_Ltrg_(0), n_Rtrg_(0) {};
	virtual ~GamePadState() {}

	virtual void Accepts(int index) override;

	Vector2 LeftDirection() {
		return Vector2(n_Lx_, n_Ly_);
	}
	Vector2 RightDirection() {
		return Vector2(n_Rx_, n_Ry_); 
	}

	float LeftTrigger() { 
		return n_Ltrg_; 
	}
	float RightTrigger() {
		return n_Rtrg_;
	}

private:
	float n_Lx_, n_Ly_;
	float n_Rx_, n_Ry_;
	float n_Ltrg_, n_Rtrg_;
};