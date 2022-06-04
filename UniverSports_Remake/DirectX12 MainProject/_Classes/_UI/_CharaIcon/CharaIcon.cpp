#include "CharaIcon.h"
#include "_Classes/_ConstStrages/US2DLayer.h"

void CharaIcon::LoadAssets(std::wstring file_name) {
	sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, file_name.c_str());
}

void CharaIcon::Render(const int life, float alpha, DirectX::XMFLOAT3 pos) {
	for (int _i = 0; _i < life; ++_i) {
		DX9::SpriteBatch->Draw(
			sprite_.Get(),
			DirectX::XMFLOAT3(pos.x + SIZE * _i, pos.y, (int)US2D::Layer::MAIN::UI_LIFEICON),
			nullptr,
			DX9::Colors::RGBA(255, 255, 255, alpha),
			DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT2(0.16f, 0.16f)
		);
	}
	DX9::SpriteBatch->ResetTransform();
}