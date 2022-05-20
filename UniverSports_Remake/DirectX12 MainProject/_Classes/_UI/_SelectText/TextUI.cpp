#include "TextUI.h"

void TextUI::Initialize(int modeID, SimpleMath::Vector3 pos) {
	position_	= pos;
	scale_		= 1.0f;
	modeID_		= modeID;
}

void TextUI::LoadAsset(std::wstring file_name) {
	sprite_		= DX9::Sprite::CreateFromFile(DXTK->Device9, file_name.c_str());
}

void TextUI::Render(float alpha) {
	DX9::SpriteBatch->Draw(
		sprite_.Get(),
		position_,
		nullptr,
		DX9::Colors::RGBA(255, 255, 255, alpha),
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		SimpleMath::Vector3(CENTER_X, CENTER_Y, 0.0f),
		SimpleMath::Vector2::One * scale_
	);
}