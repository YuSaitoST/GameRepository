/**
 * @file InputChecker.h
 * @brief DirectX‚Ì“ü—Íó‘Ô‚ğŠÇ—‚·‚éƒNƒ‰ƒX
 * @author âV“¡—D‰F
 * @date 2022/02/19
 */

#pragma once

#include "InputKeyEvent.h"
#include "InputKeyState.h"
#include "InputPadEvent.h"
#include "InputPadState.h"

#define Input InputChecker::GetInctance()	

enum ARROW_KEY {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class InputChecker {
public:
	static InputChecker& GetInctance() {
		return inctance_;
	}

	void Accepts();

	bool EventCharaKey(char inputKey);
	bool EventArrowKey(ARROW_KEY inputKey);
	bool EventAnyKey();
	Vector2 EventDirection();
	
	bool StateCharaKey(char inputKey);
	bool StateArrowKey(ARROW_KEY inputKey);
	bool StateAnyKey();
	Vector2 StateDirection();

	Vector2 PadEventDirection(int index);
	Vector2 PadStateDirection(int index);

private:
	InputChecker() {
		inpEvent_.Initialize();
		inpState_.Initialize();
		padEvent_.Initialize();
		padState_.Initialize();
	}
	virtual ~InputChecker() {}

	static InputChecker inctance_;
	InputKeyEvent inpEvent_;
	InputKeyState inpState_;
	InputPadEvent padEvent_;
	InputPadState padState_;
};