#include"MoviePlayer.h"

/**
* @brief 指定したファイルを読み込む
* @param file_name ファイル名
*/
void MoviePlayer::LoadAsset(std::wstring file_name) {
	media_ = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, file_name.c_str());
}

/**
* @brief リピート再生
*/
void MoviePlayer::Update() {
	if (media_->isComplete())
		media_->Replay();
}

/**
* @brief ウィンドウサイズで描画
* @param pos_z 動画のz座標
*/
void MoviePlayer::Render() const {
	DX9::SpriteBatch->DrawSimple(media_->Get(), DirectX::SimpleMath::Vector3::Zero);
}

/**
* @brief 指定したサイズで描画
* @param pos 動画の表示座標
* @param scale 動画の表示サイズ
*/
void MoviePlayer::Render(DirectX::SimpleMath::Vector3 pos, float scale) const {
	DX9::SpriteBatch->Draw(
		media_->Get(), pos, nullptr,
		DX9::Colors::RGBA(255, 255, 255, 255),
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector2::One * scale
	);
	DX9::SpriteBatch->ResetTransform();
}