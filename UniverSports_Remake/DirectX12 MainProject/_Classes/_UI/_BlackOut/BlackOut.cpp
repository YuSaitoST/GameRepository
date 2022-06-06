#include "BlackOut.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_UI/_Fade/Fade.h"

BlackOut::BlackOut() : sprite_(DX9::SPRITE()) {
	mode_			= BLACKOUT_MODE::NONE_ANIMATION;
	alpha_			= 0.0f;
}

/**
* @brief ������
* @param state �J�n���
*/
void BlackOut::Initialize(BLACKOUT_MODE state) {
	mode_			= state;
	alpha_			= (mode_ == BLACKOUT_MODE::FADE_IN) ? 0.0f : RGBA_MAX;
}

/**
* @brief �t�@�C���ǂݍ���
*/
void BlackOut::LoadAsset() {
	sprite_			= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::BLACKOUT.c_str());
}

/**
* @brief �X�V
*/
void BlackOut::Update(float speed) {
	(mode_ == BLACKOUT_MODE::FADE_IN) ?
		FADE::In(alpha_, RGBA_MAX, speed) :
		FADE::Out(alpha_, 0.0f, speed);
}

/**
* @brief �`��
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
* @brief �t�F�[�h�̏I����Ԃ�Ԃ�
* @return �t�F�[�h�̏I�����
*/
bool BlackOut::isDone() {
	return (mode_ == BLACKOUT_MODE::FADE_IN) ?
		(alpha_ == RGBA_MAX) :
		(alpha_ == 0.0f);
}