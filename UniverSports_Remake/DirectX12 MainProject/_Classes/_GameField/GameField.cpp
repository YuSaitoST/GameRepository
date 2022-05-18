#include "GameField.h"
#include "_Classes/_FileNames/MoviesFN.h"
#include "_Classes/_FileNames/SpritesFN.h"
#include "DontDestroyOnLoad.h"

GameField::GameField(float sp_z) {
	movie_		= new MoviePlayer();
	sprite_z_	= sp_z;
}

GameField::~GameField() {
	delete movie_;
}

/**
* @brief ファイルの読み込み
*/
void GameField::LoadAsset() {
	if (DontDestroy->GameMode_.isDODGEBALL()) {
		//ドッジボール系のモードなら、通常のワイヤー画像を読み込む
		sp_wireList_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::NOMAL_WIRE.c_str()));
	}
	else {
		// それ以外の場合、ワイヤーをゴールとして用いるため、専用の画像を読み込む
		for (int _i = 0; _i <= 2; _i += 2) {
			sp_wireList_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::COLOR_WIRE[DontDestroy->ChoseColor_[_i]][_i].c_str()));
			sp_wireList_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::COLOR_WIRE[DontDestroy->ChoseColor_[_i + 1]][_i + 1].c_str()));
		}
	}

	sp_hole_ = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::HOLE.c_str());
	movie_->LoadAsset(USFN_MV::MAIN_BG);
	movie_->Play();
}

/**
* @brief 更新
*/
void GameField::Update() {
	movie_->Update();
}

/**
* @brief 描画
*/
void GameField::Render() {
	for (DX9::SPRITE sp : sp_wireList_)
		DX9::SpriteBatch->DrawSimple(sp.Get(), DirectX::XMFLOAT3(0.0f, 0.0f, -981.0f));

	DX9::SpriteBatch->DrawSimple(sp_hole_.Get(), DirectX::XMFLOAT3(0.0f, 0.0f, sprite_z_));

	movie_->Render();
}