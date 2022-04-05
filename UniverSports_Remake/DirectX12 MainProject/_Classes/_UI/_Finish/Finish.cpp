#include "Finish.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

Finish::Finish() {
	sprite_			= nullptr;
	position_		= SimpleMath::Vector3::Zero;
	movement_move_	= 0.0f;
	movement_alpha_ = 0.0f;
	time_display_	= 0.0f;
	alpha_			= 0.0f;
}

void Finish::Initialize() {
	position_		= SimpleMath::Vector3(1280.0f, 0.0f, -9999.0f);
	movement_move_	= MOVEMENT / GAME_CONST.FN_TIME_MOVE;
	movement_alpha_ = 255.0f / GAME_CONST.FN_TIME_ALPHA;
	time_display_	= GAME_CONST.FN_TIME_DISPLAY;
	alpha_			= 255.0f;
}

void Finish::LoadAssets() {
	sprite_			= DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Main\\_Finish\\finish.png");
}

void Finish::Update(const float deltaTime) {
	position_.x		= std::max(0.0f, position_.x - movement_move_ * deltaTime);

	if (position_.x == 0.0f)
		time_display_	= std::max(0.0f, time_display_ - GAME_CONST.FN_TIME_DISPLAY * deltaTime);

	if (position_.x == 0.0f && time_display_ == 0.0f)
		alpha_			= std::max(0.0f, alpha_ - movement_alpha_ * deltaTime);
}

void Finish::Render() {
	DX9::SpriteBatch->DrawSimple(
		sprite_.Get(),
		position_,
		RECT(0.0f, 0.0f, 1280.0f, 720.0f), 
		DX9::Colors::RGBA(255, 255, 255, alpha_)
	);
}