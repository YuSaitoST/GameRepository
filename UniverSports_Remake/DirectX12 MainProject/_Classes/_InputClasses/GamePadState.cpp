#include "GamePadState.h"

/**
* @brief “ü—Íó‘Ô‚ð’²‚×‚é
* @param index ƒQ[ƒ€ƒpƒbƒh‚Ì”Ô†
*/
void GamePadState::Accepts(int index) {
	//Œ…ã‚ª‚è–hŽ~
	flag_	= 0;
	direct_ = Vector2::Zero;

	//Šeƒrƒbƒg‚É“ü—Íó‘Ô‚ð“ü‚ê‚é
	flag_ |= (bool)DXTK->GamePadState[index].buttons.a					<< P_A			 ;
	flag_ |= (bool)DXTK->GamePadState[index].buttons.b					<< P_B			 ;
	flag_ |= (bool)DXTK->GamePadState[index].buttons.x					<< P_X			 ;
	flag_ |= (bool)DXTK->GamePadState[index].buttons.y					<< P_Y			 ;
	flag_ |= (bool)DXTK->GamePadState[index].dpad.up					<< P_UP			 ;
	flag_ |= (bool)DXTK->GamePadState[index].dpad.down					<< P_DOWN		 ;
	flag_ |= (bool)DXTK->GamePadState[index].dpad.left					<< P_LEFT		 ;
	flag_ |= (bool)DXTK->GamePadState[index].dpad.right					<< P_RIGHT		 ;
	flag_ |= (bool)DXTK->GamePadState[index].IsLeftThumbStickUp()		<< STICK_L_UP	 ;
	flag_ |= (bool)DXTK->GamePadState[index].IsLeftThumbStickDown()		<< STICK_L_DOWN  ;
	flag_ |= (bool)DXTK->GamePadState[index].IsLeftThumbStickLeft()		<< STICK_L_LEFT  ;
	flag_ |= (bool)DXTK->GamePadState[index].IsLeftThumbStickRight()	<< STICK_L_RIGHT ;
	flag_ |= (bool)DXTK->GamePadState[index].IsRightThumbStickUp()		<< STICK_R_UP	 ;
	flag_ |= (bool)DXTK->GamePadState[index].IsRightThumbStickDown()	<< STICK_R_DOWN  ;
	flag_ |= (bool)DXTK->GamePadState[index].IsRightThumbStickLeft()	<< STICK_R_LEFT  ;
	flag_ |= (bool)DXTK->GamePadState[index].IsRightThumbStickRight()	<< STICK_R_RIGHT ;
	flag_ |= (bool)DXTK->GamePadState[index].IsLeftShoulderPressed()	<< SHOULDER_L	 ;
	flag_ |= (bool)DXTK->GamePadState[index].IsRightShoulderPressed()	<< SHOULDER_R	 ;
	flag_ |= (bool)DXTK->GamePadState[index].IsLeftTriggerPressed()		<< TRIGGER_L	 ;
	flag_ |= (bool)DXTK->GamePadState[index].IsRightTriggerPressed()	<< TRIGGER_R	 ;

	//0.0`1.0‚ÅŽæ‚é“ü—Í
	direct_L_.x	= DXTK->GamePadState[index].thumbSticks.leftX;
	direct_L_.y	= DXTK->GamePadState[index].thumbSticks.leftY;
	direct_R_.x	= DXTK->GamePadState[index].thumbSticks.rightX;
	direct_R_.y	= DXTK->GamePadState[index].thumbSticks.rightY;
	n_Ltrg_		= DXTK->GamePadState[index].triggers.left;
	n_Rtrg_		= DXTK->GamePadState[index].triggers.right;
}