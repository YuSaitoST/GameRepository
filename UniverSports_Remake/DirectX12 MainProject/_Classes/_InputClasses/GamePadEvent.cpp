#include "GamePadEvent.h"

void GamePadEvent::Accepts(int index) {
	// Œ…ã‚ª‚è–hŽ~
	flag_ = 0;

	/*
		Šebit‚É“ü—Íó‘Ô‚ð“ü‚ê‚é
		‘«‚·——R‚ÍA“¯Žž‰Ÿ‚µ‚ð”»’è‚Å‚«‚é‚æ‚¤‚É‚·‚é‚½‚ß
	*/
	flag_ += DXTK->GamePadEvent[index].a				? (1 << A			 ) : 0;
	flag_ += DXTK->GamePadEvent[index].b				? (1 << B			 ) : 0;
	flag_ += DXTK->GamePadEvent[index].x				? (1 << X			 ) : 0;
	flag_ += DXTK->GamePadEvent[index].y				? (1 << Y			 ) : 0;
	flag_ += DXTK->GamePadEvent[index].dpadUp			? (1 << P_UP		 ) : 0;
	flag_ += DXTK->GamePadEvent[index].dpadDown			? (1 << P_DOWN		 ) : 0;
	flag_ += DXTK->GamePadEvent[index].dpadLeft			? (1 << P_LEFT		 ) : 0;
	flag_ += DXTK->GamePadEvent[index].dpadRight		? (1 << P_RIGHT		 ) : 0;
	flag_ += DXTK->GamePadEvent[index].leftStickUp		? (1 << STICK_L_UP	 ) : 0;
	flag_ += DXTK->GamePadEvent[index].leftStickDown	? (1 << STICK_L_DOWN ) : 0;
	flag_ += DXTK->GamePadEvent[index].leftStickLeft	? (1 << STICK_L_LEFT ) : 0;
	flag_ += DXTK->GamePadEvent[index].leftStickRight	? (1 << STICK_L_RIGHT) : 0;
	flag_ += DXTK->GamePadEvent[index].rightStickUp		? (1 << STICK_R_UP	 ) : 0;
	flag_ += DXTK->GamePadEvent[index].rightStickDown	? (1 << STICK_R_DOWN ) : 0;
	flag_ += DXTK->GamePadEvent[index].rightStickLeft	? (1 << STICK_R_LEFT ) : 0;
	flag_ += DXTK->GamePadEvent[index].rightStickRight	? (1 << STICK_R_RIGHT) : 0;
	flag_ += DXTK->GamePadEvent[index].leftShoulder		? (1 << SHOULDER_L	 ) : 0;
	flag_ += DXTK->GamePadEvent[index].rightShoulder	? (1 << SHOULDER_R	 ) : 0;
	flag_ += DXTK->GamePadEvent[index].leftTrigger		? (1 << TRIGGER_L	 ) : 0;
	flag_ += DXTK->GamePadEvent[index].rightTrigger		? (1 << TRIGGER_R	 ) : 0;
}