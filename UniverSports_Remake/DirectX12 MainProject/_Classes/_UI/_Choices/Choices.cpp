#include "Choices.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_StandardCalculation/StandardCalculation.h"

Choices::Choices() {
	se_choice_ = new SoundPlayer();
	se_choice_->Initialize(USFN_SOUND::SE::CHOICES, SOUND_TYPE::SE, 0.0f);
	isSelected = 0;
	putCount_ = 0;
}

void Choices::Update(int choices, bool low, bool high) {
	if (putCount_ == 0) {
		isSelected +=
			(high) ? 1 :
			(low) ? -1 : 0;
	}

	StandardCalculation::ValueLoop(isSelected, 0, choices - 1);

	if (low || high) {
		se_choice_->PlayOneShot();
		putCount_ += 1;
	}
}