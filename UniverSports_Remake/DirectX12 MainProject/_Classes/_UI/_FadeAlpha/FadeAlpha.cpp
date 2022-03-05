#include "FadeAlpha.h"

FadeAlpha::FadeAlpha(float alpha, float speed) {
	ui_alpha_	= alpha;
	speed_		= speed;
}

void FadeAlpha::Update(const float deltaTime) {
	ui_alpha_ = std::min(ui_alpha_ + speed_ * deltaTime, MAX);
}

void FadeAlpha::FadeIn() {
	
}

void FadeAlpha::FadeOut() {

}