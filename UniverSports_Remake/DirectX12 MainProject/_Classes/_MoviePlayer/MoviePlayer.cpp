#include"MoviePlayer.h"

MoviePlayer::MoviePlayer(SimpleMath::Vector3 pos, float scale) {
	media_		= nullptr;
	position_	= pos;
	scale_		= scale;
}

void MoviePlayer::LoadAsset(std::wstring file_name) {
	media_		= DX9::MediaRenderer::CreateFromFile(DXTK->Device9, file_name.c_str());
}

void MoviePlayer::Update() {
	if (media_->isComplete())
		media_->Replay();
}

void MoviePlayer::Render() const {
	//DX9::SpriteBatch->ResetTransform();

	DX9::SpriteBatch->Draw(
		media_->Get(),
		position_,
		nullptr,  // 値を設定しない->デフォルト設定にしている
		DX9::Colors::RGBA(255, 255, 255, 255),
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		SimpleMath::Vector2::One * scale_
	);

	//DX9::SpriteBatch->ResetTransform();
}