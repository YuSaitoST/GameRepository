#pragma once

#include "InputBase.h"

#define GAME_PAD DXTK_GAMEPAD

enum PAD_KEY {
	DPAD_UP,
	DPAD_DOWN,
	DPAD_LEFT,
	DPAD_RIGHT,
	SHOULDER_LEFT,
	SHOULDER_RIGHT,
	START_BUTTON,
	BACK_BUTTON,
	Y,
	B,
	A,
	X
};

enum PAD_VARIABLE {
	TRIGGER_LEFT,
	TRIGGER_RIGHT
};

class InputBasePad : public InputBase {
public:
	inline void ResetMember() {
		std::fill(std::begin(key_flag_), std::end(key_flag_), 0);
		
		for (int index = 0; index < GAME_PAD; index++) {
			trigger_[index][0] = 0.0f;
			trigger_[index][1] = 0.0f;
		}

		std::fill(std::begin(direct_), std::end(direct_), Vector2::Zero);
	}

	inline bool SwitchKey(PAD_KEY inputKey, int index) {
		//
	}

	inline float VarivableKey(PAD_VARIABLE inputKey, int index) {
		//
	}

	inline bool AnyKey(int index) {
		//
	}

	inline Vector2 Direction(int index) {
		direct_[index].Normalize();
		return direct_[index];
	}

protected:
	unsigned int key_flag_[GAME_PAD];
	float trigger_[GAME_PAD][2];
	Vector2 direct_[GAME_PAD];
};