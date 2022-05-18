#pragma once

#include "_Classes/_SoundPlayer/SoundPlayer.h"

class Choices {
public:
	Choices();
	virtual ~Choices() { delete se_choice_; };

	void Update(int choices, bool low, bool high);
	int SelectNum() const { return isSelected; };
	void NextSelectOn(const bool on) { putCount_ = (int)on; }

private:
	SoundPlayer* se_choice_;
	int isSelected;
	int putCount_;
};