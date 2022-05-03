#include "KeyBoadState.h"

void KeyBoadState::Accepts() {
	// Œ…ã‚ª‚è–hŽ~
	flag_	= 0;
	direct_ = Vector2::Zero;

	// Šeƒrƒbƒg‚É“ü—Íó‘Ô‚ð“ü‚ê‚é
	flag_ |= (bool)DXTK->KeyState->A     << A    ;
	flag_ |= (bool)DXTK->KeyState->B     << B    ;
	flag_ |= (bool)DXTK->KeyState->C     << C    ;
	flag_ |= (bool)DXTK->KeyState->D     << D    ;
	flag_ |= (bool)DXTK->KeyState->E     << E    ;
	flag_ |= (bool)DXTK->KeyState->F     << F    ;
	flag_ |= (bool)DXTK->KeyState->G     << G    ;
	flag_ |= (bool)DXTK->KeyState->H     << H    ;
	flag_ |= (bool)DXTK->KeyState->I     << I    ;
	flag_ |= (bool)DXTK->KeyState->J     << J    ;
	flag_ |= (bool)DXTK->KeyState->K     << K    ;
	flag_ |= (bool)DXTK->KeyState->L     << L    ;
	flag_ |= (bool)DXTK->KeyState->M     << M    ;
	flag_ |= (bool)DXTK->KeyState->N     << N    ;
	flag_ |= (bool)DXTK->KeyState->O     << O    ;
	flag_ |= (bool)DXTK->KeyState->P     << P    ;
	flag_ |= (bool)DXTK->KeyState->Q     << Q    ;
	flag_ |= (bool)DXTK->KeyState->R     << R    ;
	flag_ |= (bool)DXTK->KeyState->S     << S    ;
	flag_ |= (bool)DXTK->KeyState->T     << T    ;
	flag_ |= (bool)DXTK->KeyState->U     << U    ;
	flag_ |= (bool)DXTK->KeyState->V     << V    ;
	flag_ |= (bool)DXTK->KeyState->W     << W    ;
	flag_ |= (bool)DXTK->KeyState->X     << X    ;
	flag_ |= (bool)DXTK->KeyState->Y     << Y    ;
	flag_ |= (bool)DXTK->KeyState->Z     << Z    ;
	flag_ |= (bool)DXTK->KeyState->Up    << UP   ;
	flag_ |= (bool)DXTK->KeyState->Down  << DOWN ;
	flag_ |= (bool)DXTK->KeyState->Left  << LEFT ;
	flag_ |= (bool)DXTK->KeyState->Right << RIGHT;
	flag_ |= (bool)DXTK->KeyState->Tab   << TAB	;
}