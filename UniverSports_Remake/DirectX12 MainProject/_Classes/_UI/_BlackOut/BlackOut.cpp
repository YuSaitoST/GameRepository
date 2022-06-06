#include "BlackOut.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_UI/_Fade/Fade.h"

BlackOut::BlackOut() : sprite_(DX9::SPRITE()) {
	mode_			= BLACKOUT_MODE::NONE_ANIMATION;
	alpha_			= 0.0f;
}

/**
* @brief 初期化
* @param state 開始状態
*/
void BlackOut::Initialize(BLACKOUT_MODE state) {
	mode_			= state;
	alpha_			= (mode_ == BLACKOUT_MODE::FADE_IN) ? 0.0f : RGBA_MAX;
}

/**
* @brief ファイル読み込み
*/
void BlackOut::LoadAsset() {
	sprite_			= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::BLACKOUT.c_str());
}

/**
* @brief 更新
*/
void BlackOut::Update(float speed) {
	(mode_ == BLACKOUT_MODE::FADE_IN) ?
		FADE::In(alpha_, RGBA_MAX, speed) :
		FADE::Out(alpha_, 0.0f, speed);
}

/**
* @brief 描画
*/
void BlackOut::Render() {
	DX9::SpriteBatch->DrawSimple(
		sprite_.Get(),
		DirectX::XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::GENERIC::BLACKOUT),
		nullptr,
		DX9::Colors::RGBA(0.0f, 0.0f, 0.0f, alpha_)
	);
}

/**
* @brief フェードの終了状態を返す
* @return フェードの終了状態
*/
bool BlackOut::isDone() {
	return (mode_ == BLACKOUT_MODE::FADE_IN) ?
		(alpha_ == RGBA_MAX) :
		(alpha_ == 0.0f);
}