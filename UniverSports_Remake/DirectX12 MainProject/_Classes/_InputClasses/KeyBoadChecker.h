#pragma once

#include "KeyBoadEvent.h"
#include "KeyBoadState.h"

class KeyBoadChecker {
public:
	KeyBoadChecker() {}
	virtual ~KeyBoadChecker() {}

	void Accepts(){
		inpEvent_.Accepts(); inpState_.Accepts();
	}

	bool EventOnOffKey(KEY inputKey){
		return inpEvent_.OnOffKey(inputKey);
	}
	bool EventAnyKey(){
		return inpEvent_.AnyKey();
	}
	Vector2 EventDirection(){
		return inpEvent_.Direction();
	}
	
	bool StateOnOffKey(KEY inputKey){
		return inpState_.OnOffKey(inputKey);
	}
	bool StateAnyKey(){
		return inpState_.AnyKey();
	}
	Vector2 StateDirection(){
		return inpState_.Direction();
	}

private:
	KeyBoadEvent inpEvent_;
	KeyBoadState inpState_;
};