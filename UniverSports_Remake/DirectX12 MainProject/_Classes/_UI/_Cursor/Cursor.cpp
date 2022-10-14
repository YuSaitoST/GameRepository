#include "Cursor.h"
#include "_Classes/_InputManager/UseKeyChecker.h"

using namespace DirectX;

Cursor::Cursor() : sp_(DX9::SPRITE()), pos_(DirectX::XMFLOAT3()) {
	choices_	= std::make_unique<Choices>();
}

void Cursor::Initialize(float posx, float posy, float moved) {
	choices_->Initialize();
	pos_	= SimpleMath::Vector3(posx, posy, -2.0f);
	startPos_Y_ = posy;
	moved_	= moved;
}

void Cursor::LoadAsset(std::wstring file_name) {
	sp_ = DX9::Sprite::CreateFromFile(DXTK->Device9, file_name.c_str());
}

bool Cursor::Update(int choices, bool up, bool down) {
	const int oldID = choices_->SelectNum();

	choices_->Update(choices, up, down);
	choices_->NextSelectOn((up || down));  // ’·‰Ÿ‚µ‹ÖŽ~

	pos_.y = choices_->SelectNum() * moved_ + startPos_Y_;

	return (oldID != choices_->SelectNum());
}

void Cursor::Render(float alpha) const {
	DX9::SpriteBatch->DrawSimple(
		sp_.Get(),
		SimpleMath::Vector3(pos_.x, pos_.y, -2.0f),
		nullptr,
		DX9::Colors::RGBA(255, 255, 255, (int)alpha)
	);
}