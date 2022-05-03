#include "GamePadEvent.h"

void GamePadEvent::Accepts(int index) {
	// Œ…ã‚ª‚è–hŽ~
	flag_	= 0;
	direct_ = Vector2::Zero;

	// Šeƒrƒbƒg‚É“ü—Íó‘Ô‚ð“ü‚ê‚é
	flag_ |= (bool)DXTK->GamePadEvent[index].a				<< P_A			 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].b				<< P_B			 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].x				<< P_X			 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].y				<< P_Y			 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].dpadUp			<< P_UP			 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].dpadDown		<< P_DOWN		 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].dpadLeft		<< P_LEFT		 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].dpadRight		<< P_RIGHT		 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].leftStickUp	<< STICK_L_UP	 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].leftStickDown	<< STICK_L_DOWN  ;
	flag_ |= (bool)DXTK->GamePadEvent[index].leftStickLeft	<< STICK_L_LEFT  ;
	flag_ |= (bool)DXTK->GamePadEvent[index].leftStickRight	<< STICK_L_RIGHT ;
	flag_ |= (bool)DXTK->GamePadEvent[index].rightStickUp	<< STICK_R_UP	 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].rightStickDown	<< STICK_R_DOWN  ;
	flag_ |= (bool)DXTK->GamePadEvent[index].rightStickLeft	<< STICK_R_LEFT  ;
	flag_ |= (bool)DXTK->GamePadEvent[index].rightStickRight<< STICK_R_RIGHT ;
	flag_ |= (bool)DXTK->GamePadEvent[index].leftShoulder	<< SHOULDER_L	 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].rightShoulder	<< SHOULDER_R	 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].leftTrigger	<< TRIGGER_L	 ;
	flag_ |= (bool)DXTK->GamePadEvent[index].rightTrigger	<< TRIGGER_R	 ;
}