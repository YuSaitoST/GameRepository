#include "BlackOut.h"

BlackOut::BlackOut() {
	mode_			= BLACKOUT_MODE::NONE_ANIMATION;
	sprite_			= nullptr;
	alpha_			= 0.0f;
	speed_fadein_	= 0.0f;
	speed_fadeout_	= 0.0f;
	time_delta_		= 0.0f;
}

void BlackOut::Initialize(BLACKOUT_MODE state) {
	mode_			= state;
	alpha_			= (mode_ == BLACKOUT_MODE::FADE_IN) ? 0.0f : RGBA_MAX;
	speed_fadein_	= RGBA_MAX / TIME_FADEIN;
	speed_fadeout_	= RGBA_MAX / TIME_FADEOUT;
}

void BlackOut::LoadAsset() {
	sprite_			= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Result\\blackOut.png");
}

void BlackOut::Update(const float deltaTime) {
	time_delta_		= deltaTime;

	(mode_ == BLACKOUT_MODE::FADE_IN) ?
		FadeIn() :
		FadeOut();
}

void BlackOut::Render() {
	DX9::SpriteBatch->DrawSimple(
		sprite_.Get(),
		SimpleMath::Vector3(0.0f, 0.0f, -9999.0f),
		nullptr,
		DX9::Colors::RGBA(RGBA_MAX, RGBA_MAX, RGBA_MAX, alpha_)
	);
}

bool BlackOut::isDone() {
	return (mode_ == BLACKOUT_MODE::FADE_IN) ?
		(alpha_ == RGBA_MAX) :
		(alpha_ == 0.0f);
}

void BlackOut::FadeIn() {
	alpha_			= std::min(alpha_ + speed_fadein_ * time_delta_, RGBA_MAX);
}

void BlackOut::FadeOut() {
	alpha_			= std::max(0.0f, alpha_ - speed_fadeout_ * time_delta_);
}