#include "KeyBoadEvent.h"

void KeyBoadEvent::Accepts() {
	// Œ…ã‚ª‚è–h~
	flag_	= 0;
	direct_ = Vector2::Zero;

	// Šeƒrƒbƒg‚É“ü—Íó‘Ô‚ğ“ü‚ê‚é
	flag_ |= (bool)DXTK->KeyEvent->pressed.A		<< A    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.B		<< B    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.C		<< C    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.D		<< D    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.E		<< E    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.F		<< F    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.G		<< G    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.H		<< H    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.I		<< I    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.J		<< J    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.K		<< K    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.L		<< L    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.M		<< M    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.N		<< N    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.O		<< O    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.P		<< P    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.Q		<< Q    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.R		<< R    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.S		<< S    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.T		<< T    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.U		<< U    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.V		<< V    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.W		<< W    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.X		<< X    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.Y		<< Y    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.Z		<< Z    ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.Up		<< UP   ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.Down		<< DOWN ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.Left		<< LEFT ;
	flag_ |= (bool)DXTK->KeyEvent->pressed.Right	<< RIGHT;
	flag_ |= (bool)DXTK->KeyEvent->pressed.Tab		<< TAB	;
}