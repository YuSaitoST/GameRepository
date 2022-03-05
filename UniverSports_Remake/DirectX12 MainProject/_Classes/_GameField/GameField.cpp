#include "GameField.h"

GameField::GameField(SimpleMath::Vector3 pos, float sp_z, float scale) {
	movie_	= new MoviePlayer(pos, scale);
	pos_	= SimpleMath::Vector3(pos.x, pos.y, sp_z);
}

GameField::~GameField() {
	delete movie_;
}

void GameField::LoadAsset(std::wstring m_file_name, std::wstring s_file_name) {
	sprite_	= DX9::Sprite::CreateFromFile(DXTK->Device9, s_file_name.c_str());
	movie_->LoadAsset(m_file_name);
	movie_->Play();
}

void GameField::Update() {
	movie_->Update();
}

void GameField::Render() {
	DX9::SpriteBatch->DrawSimple(
		sprite_.Get(),
		pos_
	);

	movie_->Render();
}