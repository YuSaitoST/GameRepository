#include "KeyBoadState.h"

void KeyBoadState::Accepts() {
	// Œ…ã‚ª‚è–hŽ~
	flag_ = 0;
	direct_ = Vector2::Zero;

	/*
		Šebit‚É“ü—Íó‘Ô‚ð“ü‚ê‚é
		‘«‚·——R‚ÍA“¯Žž‰Ÿ‚µ‚ð”»’è‚Å‚«‚é‚æ‚¤‚É‚·‚é‚½‚ß
	*/
	flag_ += DXTK->KeyState->A     ? (1 << A    ) : 0;
	flag_ += DXTK->KeyState->B     ? (1 << B    ) : 0;
	flag_ += DXTK->KeyState->C     ? (1 << C    ) : 0;
	flag_ += DXTK->KeyState->D     ? (1 << D    ) : 0;
	flag_ += DXTK->KeyState->E     ? (1 << E    ) : 0;
	flag_ += DXTK->KeyState->F     ? (1 << F    ) : 0;
	flag_ += DXTK->KeyState->G     ? (1 << G    ) : 0;
	flag_ += DXTK->KeyState->H     ? (1 << H    ) : 0;
	flag_ += DXTK->KeyState->I     ? (1 << I    ) : 0;
	flag_ += DXTK->KeyState->J     ? (1 << J    ) : 0;
	flag_ += DXTK->KeyState->K     ? (1 << K    ) : 0;
	flag_ += DXTK->KeyState->L     ? (1 << L    ) : 0;
	flag_ += DXTK->KeyState->M     ? (1 << M    ) : 0;
	flag_ += DXTK->KeyState->N     ? (1 << N    ) : 0;
	flag_ += DXTK->KeyState->O     ? (1 << O    ) : 0;
	flag_ += DXTK->KeyState->P     ? (1 << P    ) : 0;
	flag_ += DXTK->KeyState->Q     ? (1 << Q    ) : 0;
	flag_ += DXTK->KeyState->R     ? (1 << R    ) : 0;
	flag_ += DXTK->KeyState->S     ? (1 << S    ) : 0;
	flag_ += DXTK->KeyState->T     ? (1 << T    ) : 0;
	flag_ += DXTK->KeyState->U     ? (1 << U    ) : 0;
	flag_ += DXTK->KeyState->V     ? (1 << V    ) : 0;
	flag_ += DXTK->KeyState->W     ? (1 << W    ) : 0;
	flag_ += DXTK->KeyState->X     ? (1 << X    ) : 0;
	flag_ += DXTK->KeyState->Y     ? (1 << Y    ) : 0;
	flag_ += DXTK->KeyState->Z     ? (1 << Z    ) : 0;
	flag_ += DXTK->KeyState->Up    ? (1 << UP   ) : 0;
	flag_ += DXTK->KeyState->Down  ? (1 << DOWN ) : 0;
	flag_ += DXTK->KeyState->Left  ? (1 << LEFT ) : 0;
	flag_ += DXTK->KeyState->Right ? (1 << RIGHT) : 0;
}