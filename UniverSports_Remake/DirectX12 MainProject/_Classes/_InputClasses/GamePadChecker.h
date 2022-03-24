#pragma once

#include "GamePadEvent.h"
#include "GamePadState.h"

#define N_PAD DXTK_GAMEPAD

class GamePadChecker {
public:
	GamePadChecker() {}
	virtual ~GamePadChecker() {}

	void Accepts(int index) {
		inpEvent_[index].Accepts(index);
		inpState_[index].Accepts(index);
	}

	bool EventOnOffKey(int index, PAD inputKey) {
		return inpEvent_[index].OnOffKey(inputKey);
	}
	bool EventAnyKey(int index) {
		return inpEvent_[index].AnyKey();
	}
	Vector2 EventDirection4(int index) {
		return inpEvent_[index].Direction();
	}

	bool StateOnOffKey(int index, PAD inputKey) {
		return inpState_[index].OnOffKey(inputKey);
	}
	bool StateAnyKey(int index) {
		return inpState_[index].AnyKey();
	}
	Vector2 StateDirection4(int index) {
		return inpState_[index].Direction();
	}

	Vector2 LeftStateDirection360(int index) {
		return inpState_[index].LeftDirection();
	}
	Vector2 RightStateDirection360(int index) {
		return inpState_[index].RightDirection();
	}

	float LeftTrigger(int index) {
		return inpState_[index].LeftTrigger();
	}
	float RightTrigger(int index) {
		return inpState_[index].RightTrigger();
	}

private:
	GamePadEvent inpEvent_[N_PAD];
	GamePadState inpState_[N_PAD];
};