#include "Choices.h"

Choices::Choices(int choices) {
	se_choice_ = new SoundPlayer();
	se_choice_->Initialize(L"_Sounds\\_SE\\se_choise.wav", SOUND_TYPE::SE);
	isSelected = 0;
	CHOICES = choices;
	putCount_ = 0;
}

void Choices::Update(bool low, bool high) {
	if (putCount_ == 0) {
		isSelected +=
			(high) ? 1 :
			(low) ? -1 : 0;

		if (low || high)
			putCount_ += 1;
	}

	ValueLoop(isSelected, 0, CHOICES - 1);

	if (low || high)
		se_choice_->PlayOneShot();
}

void Choices::ValueLoop(int& num, int min, int max) {
	if (num < min)
		num = max;

	if (max < num)
		num = min;
}