#include "InputPadState.h"

void InputPadState::Initialize() {
	ResetMember();
}

void InputPadState::Accepts() {
	ResetMember();

	for (int index = 0; index < GAME_PAD; index++) {
		key_flag_[index] += DXTK->GamePadState[index].IsDPadUpPressed() ? (1 << DPAD_UP) : 0;
		key_flag_[index] += DXTK->GamePadState[index].IsDPadDownPressed() ? (1 << DPAD_DOWN) : 0;
		key_flag_[index] += DXTK->GamePadState[index].IsDPadLeftPressed() ? (1 << DPAD_LEFT) : 0;
		key_flag_[index] += DXTK->GamePadState[index].IsDPadRightPressed() ? (1 << DPAD_RIGHT) : 0;
		key_flag_[index] += DXTK->GamePadState[index].IsLeftShoulderPressed() ? (1 << SHOULDER_LEFT) : 0;
		key_flag_[index] += DXTK->GamePadState[index].IsRightShoulderPressed() ? (1 << SHOULDER_RIGHT) : 0;
		key_flag_[index] += DXTK->GamePadState[index].IsStartPressed() ? (1 << START_BUTTON) : 0;
		key_flag_[index] += DXTK->GamePadState[index].IsBackPressed() ? (1 << BACK_BUTTON) : 0;
		key_flag_[index] += DXTK->GamePadState[index].IsYPressed() ? (1 << Y) : 0;
		key_flag_[index] += DXTK->GamePadState[index].IsBPressed() ? (1 << B) : 0;
		key_flag_[index] += DXTK->GamePadState[index].IsAPressed() ? (1 << A) : 0;
		key_flag_[index] += DXTK->GamePadState[index].IsXPressed() ? (1 << X) : 0;
	}

	for (int index = 0; index < GAME_PAD; index++) {
		direct_[index].x = DXTK->GamePadState[index].thumbSticks.leftX;
		direct_[index].y = DXTK->GamePadState[index].thumbSticks.leftY;
		trigger_[index][TRIGGER_LEFT]  = DXTK->GamePadState[index].triggers.left;
		trigger_[index][TRIGGER_RIGHT] = DXTK->GamePadState[index].triggers.right;
	}
}