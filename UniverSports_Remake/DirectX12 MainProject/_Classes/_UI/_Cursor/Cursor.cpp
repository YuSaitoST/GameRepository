#include "Cursor.h"

Cursor::Cursor(int selects) {
	choices_	= new Choices(selects);
	sp_			= nullptr;
	pos_		= SimpleMath::Vector3::Zero;
	SELECTS		= selects;
}

Cursor::~Cursor() {
	delete choices_;
}

void Cursor::Initialize() {
	pos_ = SimpleMath::Vector3(POS_X, POS_Y, -2.0f);
}

void Cursor::LoadAsset(std::wstring file_name) {
	sp_ = DX9::Sprite::CreateFromFile(DXTK->Device9, file_name.c_str());
}

void Cursor::Update() {
	choices_->Update(Press.DownKey(0), Press.UpKey(0));

	pos_.y = choices_->SelectNum() * MOVE_Y + POS_Y;
}

void Cursor::Render(float alpha) const {
	DX9::SpriteBatch->DrawSimple(
		sp_.Get(),
		SimpleMath::Vector3(pos_.x,pos_.y,-2.0f),
		nullptr,
		DX9::Colors::RGBA(255, 255, 255, (int)alpha)
	);
}