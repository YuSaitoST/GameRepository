#pragma once

#include "KeyBoadEvent.h"
#include "KeyBoadState.h"

enum ARROW_KEY {
	K_UP, K_DOWN, K_LEFT, K_RIGHT
};

class KeyBoadChecker {
public:
	KeyBoadChecker() {}
	virtual ~KeyBoadChecker() {}

	void Accepts(){ inpEvent_.Accepts(); inpState_.Accepts(); }

	bool EventCharaKey(char inputKey){ return inpEvent_.CharaKey(inputKey); }
	bool EventArrowKey(ARROW_KEY inputKey){ return inpEvent_.ArrowKey(inputKey); }
	bool EventAnyKey(){ return inpEvent_.AnyKey(); }
	Vector2 EventDirection(){ return inpEvent_.Direction(); }
	
	bool StateCharaKey(char inputKey){ return inpState_.CharaKey(inputKey); }
	bool StateArrowKey(ARROW_KEY inputKey){ return inpState_.ArrowKey(inputKey); }
	bool StateAnyKey(){ return inpState_.AnyKey(); }
	Vector2 StateDirection(){ return inpState_.Direction(); }

private:
	KeyBoadEvent inpEvent_;
	KeyBoadState inpState_;
};