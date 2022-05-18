#include "IconAnimator.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_UI/_Fade/Fade.h"

bool IconAnimator::display_(false);

IconAnimator::IconAnimator() : alpha_(0) {
	for (int _i = 0; _i <= 2; _i += 2) {
		icon_[_i]		= new CharaIcon();
		icon_[_i + 1]	= new CharaIcon();
	}

	display_time_ = new CountTimer(3);
}

IconAnimator::~IconAnimator() {
	delete display_time_;

	for (int _i = 3; 0 <= _i; --_i)
		delete icon_[_i];
}

void IconAnimator::Initialize() {
	for (int _i = 0; _i <= 2; _i += 2) {
		icon_[_i]->Initialize(POS_LEFTICON[_i]);
		icon_[_i + 1]->Initialize(POS_LEFTICON[_i + 1]);
	}
}

void IconAnimator::LoadAssets() {
	for (int _i = 0; _i <= 2; _i += 2) {
		icon_[_i]->LoadAssets(USFN_SP::LEFT_ICON[DontDestroy->ChoseColor_[_i]]);
		icon_[_i + 1]->LoadAssets(USFN_SP::LEFT_ICON[DontDestroy->ChoseColor_[_i + 1]]);
	}
}

void IconAnimator::Update(const float deltaTime) {
	if (display_) {
		display_time_->Update(deltaTime);
		display_ = !display_time_->TimeOut();
	}
	else
		display_time_->Reset();

	(display_) ?
		FADE::In(alpha_, 255.0f, deltaTime * SPEED_FADEIN) :
		FADE::Out(alpha_, 0.0f, deltaTime * SPEED_FADEOUT);
}

void IconAnimator::Render(const int lifeCount, int index) {
	icon_[index]->Render(lifeCount, alpha_);
}