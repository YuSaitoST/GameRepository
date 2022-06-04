#include "Finish.h"
#include "_Classes/_UI/_Fade/Fade.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_ConstStrages/US2DLayer.h"

Finish::Finish() : sprite_(DX9::SPRITE()), position_(DirectX::XMFLOAT3()) {
	movement_move_	= 0.0f;
	movement_alpha_ = 0.0f;
	time_display_	= 0.0f;
	alpha_			= 0.0f;
}

void Finish::Initialize() {
	position_		= DirectX::XMFLOAT3(1280.0f, 0.0f, (int)US2D::Layer::MAIN::UI_FINISH);
	movement_move_	= MOVEMENT / GAMES_PARAM.FN_TIME_MOVE;
	movement_alpha_ = FADE::COLORMAX / GAMES_PARAM.FN_TIME_FADEOUT;
	time_display_	= GAMES_PARAM.FN_TIME_DISPLAY;
	alpha_			= FADE::COLORMAX;
}

void Finish::LoadAssets() {
	sprite_			= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Main\\_Finish\\finish.png");
}

void Finish::Update(const float deltaTime) {
	position_.x		= std::max(0.0f, position_.x - movement_move_ * deltaTime);
	
	if (position_.x == 0.0f)
		time_display_	= std::max(0.0f, time_display_ - GAMES_PARAM.FN_TIME_DISPLAY * deltaTime);

	if (position_.x == 0.0f && time_display_ == 0.0f)
		FADE::Out(alpha_, 0.0f, deltaTime * movement_alpha_);
}

void Finish::Render() {
	DX9::SpriteBatch->DrawSimple(
		sprite_.Get(),
		position_,
		RECT(0.0f, 0.0f, 1280.0f, 720.0f), 
		DX9::Colors::RGBA(FADE::COLORMAX, FADE::COLORMAX, FADE::COLORMAX, alpha_)
	);
}