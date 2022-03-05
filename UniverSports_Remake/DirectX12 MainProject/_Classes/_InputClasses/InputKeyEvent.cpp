#include "InputKeyEvent.h"

void InputKeyEvent::Initialize() {
	ResetMember();
}

void InputKeyEvent::Accepts() {
	// Œ…ã‚ª‚è–h~A•ûŒü•Û‚Ì–h~
	ResetMember();

	/*
		Šebit‚É“ü—Íó‘Ô‚ğ“ü‚ê‚é
		‘«‚·——R‚ÍA“¯‰Ÿ‚µ‚ğ”»’è‚Å‚«‚é‚æ‚¤‚É‚·‚é‚½‚ß
	*/
	flag_ += DXTK->KeyEvent->pressed.A		? (1 << A    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.B		? (1 << B    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.C		? (1 << C    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.D		? (1 << D    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.E		? (1 << E    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.F		? (1 << F    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.G		? (1 << G    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.H		? (1 << H    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.I		? (1 << I    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.J		? (1 << J    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.K		? (1 << K    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.L		? (1 << L    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.M		? (1 << M    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.N		? (1 << N    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.O		? (1 << O    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.P		? (1 << P    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.Q		? (1 << Q    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.R		? (1 << R    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.S		? (1 << S    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.T		? (1 << T    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.U		? (1 << U    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.V		? (1 << V    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.W		? (1 << W    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.X		? (1 << X    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.Y		? (1 << Y    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.Z		? (1 << Z    ) : 0;
	flag_ += DXTK->KeyEvent->pressed.Up		? (1 << UP   ) : 0;
	flag_ += DXTK->KeyEvent->pressed.Down	? (1 << DOWN ) : 0;
	flag_ += DXTK->KeyEvent->pressed.Left	? (1 << LEFT ) : 0;
	flag_ += DXTK->KeyEvent->pressed.Right	? (1 << RIGHT) : 0;
}