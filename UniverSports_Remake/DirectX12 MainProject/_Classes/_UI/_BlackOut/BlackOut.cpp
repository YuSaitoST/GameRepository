#include "BlackOut.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_UI/_Fade/Fade.h"

BlackOut::BlackOut() {
	mode_			= BLACKOUT_MODE::NONE_ANIMATION;
	sprite_			= nullptr;
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
void BlackOut::Update(const float deltaTime) {
	(mode_ == BLACKOUT_MODE::FADE_IN) ?
		FADE::In(alpha_, RGBA_MAX, deltaTime * TIME_FADEIN) :
		FADE::Out(alpha_, 0.0f, deltaTime * TIME_FADEOUT);
}

/**
* @brief �`��
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
* @brief �t�F�[�h�̏I����Ԃ�Ԃ�
* @return �t�F�[�h�̏I�����
*/
bool BlackOut::isDone() {
	return (mode_ == BLACKOUT_MODE::FADE_IN) ?
		(alpha_ == RGBA_MAX) :
		(alpha_ == 0.0f);
}