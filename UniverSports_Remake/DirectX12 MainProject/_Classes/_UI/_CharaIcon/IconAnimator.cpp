#include "IconAnimator.h"

bool IconAnimator::display_(false);

IconAnimator::IconAnimator() : alpha_(0) {
	for (int _i = 0; _i < 4; ++_i)
		icon_[_i] = new CharaIcon();

	display_time_ = new OriTimer(3);
}

IconAnimator::~IconAnimator() {
	delete display_time_;

	for (int _i = 3; 0 <= _i; --_i)
		delete icon_[_i];
}

void IconAnimator::Initialize() {
	for (int _i = 0; _i < 4; ++_i)
		icon_[_i]->Initialize(POS_LEFTICON[_i]);
}

void IconAnimator::LoadAssets() {
	for (int _i = 0; _i < 4; ++_i)
		icon_[_i]->LoadAssets(PLICON_FILENAME[_i]);
}

void IconAnimator::Update(const float deltaTime) {
	if (display_) {
		display_time_->Update(deltaTime);
		display_ = !display_time_->TimeOut();
	}
	else
		display_time_->ResetCountTime();

	if (display_)
		FadeIn(deltaTime);
	else
		FadeOut(deltaTime);
}

void IconAnimator::Render(const int lifeCount, int index) {
	icon_[index]->Render(lifeCount, alpha_);
}

void IconAnimator::FadeIn(const float deltaTime) {
	alpha_ = std::min(alpha_ + SPEED_FADEIN * deltaTime, 255.0f);
}

void IconAnimator::FadeOut(const float deltaTime) {
	alpha_ = std::max(0.0f, alpha_ - SPEED_FADEOUT * deltaTime);
}