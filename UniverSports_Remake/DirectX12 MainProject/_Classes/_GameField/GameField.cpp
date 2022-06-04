#include "GameField.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/US2DLayer.h"
#include "DontDestroyOnLoad.h"

GameField::GameField(float sp_z) {
	movie_		= std::make_unique<MoviePlayer>();
	sprite_z_	= sp_z;
}

/**
* @brief �t�@�C���̓ǂݍ���
*/
void GameField::LoadAsset() {
	if (DontDestroy->GameMode_.isDODGEBALL()) {
		//�h�b�W�{�[���n�̃��[�h�Ȃ�A�ʏ�̃��C���[�摜��ǂݍ���
		sp_wireList_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::NOMAL_WIRE.c_str()));
	}
	else {
		// ����ȊO�̏ꍇ�A���C���[���S�[���Ƃ��ėp���邽�߁A��p�̉摜��ǂݍ���
		for (int _i = 0; _i <= 2; _i += 2) {
			sp_wireList_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::COLOR_WIRE[DontDestroy->ChoseColor_[_i]][_i].c_str()));
			sp_wireList_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::COLOR_WIRE[DontDestroy->ChoseColor_[_i + 1]][_i + 1].c_str()));
		}
	}

	sp_hole_ = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::HOLE.c_str());
	movie_->LoadAsset(USFN_MV::MAIN_BG);
	movie_->Play();
}

void GameField::Update() {
	movie_->Update();
}

void GameField::Render() {
	for (DX9::SPRITE sp : sp_wireList_)
		DX9::SpriteBatch->DrawSimple(sp.Get(), DirectX::XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::MAIN::UI_WIRE));

	DX9::SpriteBatch->DrawSimple(sp_hole_.Get(), DirectX::XMFLOAT3(0.0f, 0.0f, sprite_z_));

	movie_->Render(DirectX::XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::MAIN::BG_MOVIE));
}