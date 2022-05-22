#include "Cursor.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"

using namespace DirectX;

Cursor::Cursor() : sp_(DX9::SPRITE()), pos_(DirectX::XMFLOAT3()) {
	choices_	= new Choices();
}

Cursor::~Cursor() {
	delete choices_;
}

void Cursor::Initialize() {
	choices_->Initialize();
	pos_ = SimpleMath::Vector3(POS_X, POS_Y, -2.0f);
}

void Cursor::LoadAsset(std::wstring file_name) {
	sp_ = DX9::Sprite::CreateFromFile(DXTK->Device9, file_name.c_str());
}

void Cursor::Update(int choices) {
	choices_->Update(choices, Press.DownKey(0), Press.UpKey(0));
	choices_->NextSelectOn((Press.DownKey(0)) || (Press.UpKey(0)));  // ’·‰Ÿ‚µ‹ÖŽ~

	pos_.y = choices_->SelectNum() * MOVE_Y + POS_Y;
}

void Cursor::Render(float alpha) const {
	DX9::SpriteBatch->DrawSimple(
		sp_.Get(),
		SimpleMath::Vector3(pos_.x, pos_.y, -2.0f),
		nullptr,
		DX9::Colors::RGBA(255, 255, 255, (int)alpha)
	);
}