#include "BlackOut.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_UI/_Fade/Fade.h"

BlackOut::BlackOut() {
	mode_			= BLACKOUT_MODE::NONE_ANIMATION;
	sprite_			= nullptr;
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
void BlackOut::Update(const float deltaTime) {
	(mode_ == BLACKOUT_MODE::FADE_IN) ?
		FADE::In(alpha_, RGBA_MAX, deltaTime * TIME_FADEIN) :
		FADE::Out(alpha_, 0.0f, deltaTime * TIME_FADEOUT);
}

/**
* @brief 描画
*/
void BlackOut::Render() {
	DX9::SpriteBatch->DrawSimple(
		sprite_.Get(),
		SimpleMath::Vector3(0.0f, 0.0f, -9999.0f),
		nullptr,
		DX9::Colors::RGBA(RGBA_MAX, RGBA_MAX, RGBA_MAX, alpha_)
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