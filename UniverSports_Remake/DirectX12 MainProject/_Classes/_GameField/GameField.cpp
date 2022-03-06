#include "GameField.h"
#include "DontDestroyOnLoad.h"

GameField::GameField(SimpleMath::Vector3 pos, float sp_z, float scale) {
	movie_	= new MoviePlayer(pos, scale);
	pos_	= SimpleMath::Vector3(pos.x, pos.y, sp_z);
}

GameField::~GameField() {
	delete movie_;
}

void GameField::LoadAsset(std::wstring m_file_name, std::wstring s_file_name) {
	if (DontDestroy->GameMode_ == 0)
		sprite_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Main\\_Wire\\honeycomb_wire02.png"));
	else
		for (int _i = 0; _i < 4; ++_i)
			sprite_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, FILENAME_WIRE[DontDestroy->ChoseColor_[_i]][_i].c_str()));

	sp_hole_	= DX9::Sprite::CreateFromFile(DXTK->Device9, s_file_name.c_str());
	movie_->LoadAsset(m_file_name);
	movie_->Play();
}

void GameField::Update() {
	movie_->Update();
}

void GameField::Render() {
	for (DX9::SPRITE sp : sprite_)
		DX9::SpriteBatch->DrawSimple(sp.Get(), SimpleMath::Vector3(0.0f, 0.0f, -981.0f));

	DX9::SpriteBatch->DrawSimple(
		sp_hole_.Get(),
		pos_
	);

	movie_->Render();
}