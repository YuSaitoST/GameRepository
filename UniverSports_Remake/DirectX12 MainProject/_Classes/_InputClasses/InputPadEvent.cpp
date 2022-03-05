#include "InputPadEvent.h"

void InputPadEvent::Initialize() {
	ResetMember();
}

void InputPadEvent::Accepts() {
	ResetMember();

	for (int index = 0; index < GAME_PAD; index++) {
		key_flag_[index] += DXTK->GamePadEvent[index].dpadUp		? (1 << DPAD_UP       ) : 0;
		key_flag_[index] += DXTK->GamePadEvent[index].dpadDown		? (1 << DPAD_DOWN     ) : 0;
		key_flag_[index] += DXTK->GamePadEvent[index].dpadLeft		? (1 << DPAD_LEFT     ) : 0;
		key_flag_[index] += DXTK->GamePadEvent[index].dpadRight		? (1 << DPAD_RIGHT	  ) : 0;
		key_flag_[index] += DXTK->GamePadEvent[index].leftShoulder  ? (1 << SHOULDER_LEFT ) : 0;
		key_flag_[index] += DXTK->GamePadEvent[index].rightShoulder ? (1 << SHOULDER_RIGHT) : 0;
		key_flag_[index] += DXTK->GamePadEvent[index].start			? (1 << START_BUTTON  ) : 0;
		key_flag_[index] += DXTK->GamePadEvent[index].back			? (1 << BACK_BUTTON   ) : 0;
		key_flag_[index] += DXTK->GamePadEvent[index].y	 			? (1 << Y			  ) : 0;
		key_flag_[index] += DXTK->GamePadEvent[index].b	 			? (1 << B			  ) : 0;
		key_flag_[index] += DXTK->GamePadEvent[index].a	 			? (1 << A			  ) : 0;
		key_flag_[index] += DXTK->GamePadEvent[index].x				? (1 << X			  ) : 0;
	}

	for (int index = 0; index < GAME_PAD; index++) {
		trigger_[index][TRIGGER_LEFT]  = DXTK->GamePadEvent[index].leftTrigger;
		trigger_[index][TRIGGER_RIGHT] = DXTK->GamePadEvent[index].rightTrigger;
	}
}