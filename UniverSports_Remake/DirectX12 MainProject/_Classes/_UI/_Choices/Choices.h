#pragma once

#include "_Classes/_SoundPlayer/SoundPlayer.h"

class Choices {
public:
	Choices(int choices);
	virtual ~Choices() { delete se_choice_; };

	void Update(bool low, bool high);
	int SelectNum() const { return isSelected; };
	void NextSelectOn(const bool on) { putCount_ = (int)on; }

private:
	void ValueLoop(int& num, int min, int max);

	SoundPlayer* se_choice_;
	int CHOICES;
	int isSelected;
	int putCount_;
};