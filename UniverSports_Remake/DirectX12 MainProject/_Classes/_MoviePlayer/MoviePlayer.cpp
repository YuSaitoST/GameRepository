#include"MoviePlayer.h"

/**
* @brief �w�肵���t�@�C����ǂݍ���
* @param file_name �t�@�C����
*/
void MoviePlayer::LoadAsset(std::wstring file_name) {
	media_ = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, file_name.c_str());
}

/**
* @brief ���s�[�g�Đ�
*/
void MoviePlayer::Update() {
	if (media_->isComplete())
		media_->Replay();
}

/**
* @brief �E�B���h�E�T�C�Y�ŕ`��
* @param pos_z �����z���W
*/
void MoviePlayer::Render() const {
	DX9::SpriteBatch->DrawSimple(media_->Get(), DirectX::SimpleMath::Vector3::Zero);
}

/**
* @brief �w�肵���T�C�Y�ŕ`��
* @param pos ����̕\�����W
* @param scale ����̕\���T�C�Y
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