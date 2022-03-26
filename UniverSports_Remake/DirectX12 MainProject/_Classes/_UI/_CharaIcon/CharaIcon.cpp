#include "CharaIcon.h"

void CharaIcon::Initialize(SimpleMath::Vector3 pos) {
	pos_ = pos;
}

void CharaIcon::LoadAssets(std::wstring file_name) {
	sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, file_name.c_str());
}

void CharaIcon::Render(const int life, float alpha) {
	for (int _i = 0; _i < life; ++_i) {
		DX9::SpriteBatch->Draw(
			sprite_.Get(),
			SimpleMath::Vector3(pos_.x + SIZE * _i, pos_.y, -9980.0f),
			nullptr,
			DX9::Colors::RGBA(255, 255, 255, alpha),
			SimpleMath::Vector3::Zero,
			SimpleMath::Vector3::Zero,
			SimpleMath::Vector2(0.16f, 0.16f)
		);
	}
	DX9::SpriteBatch->ResetTransform();
}