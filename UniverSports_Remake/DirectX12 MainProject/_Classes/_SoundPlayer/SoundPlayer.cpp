#include"SoundPlayer.h"

SoundPlayer::SoundPlayer() : sound_(XAudio::SOUNDEFFECT()), bgm_instance_(XAudio::SOUNDEFFECTINSTANCE()) {
	timer_			= nullptr;
}

SoundPlayer::~SoundPlayer() {
	delete timer_;
}

/**
* @brief ������
*/
void SoundPlayer::Initialize(std::wstring file_name, SOUND_TYPE sound_type, float playTime) {
	sound_			= XAudio::CreateSoundEffect(DXTK->AudioEngine, file_name.c_str());
	bgm_instance_	= (sound_type == SOUND_TYPE::BGM) ? sound_->CreateInstance() : nullptr;
	timer_			= new CountTimer(playTime);
}

/**
* @brief �w�b�h�z���̔����������ɂ��f�o�C�X���Z�b�g���ɍĐ�������
*/
void SoundPlayer::OnRestartSound() {
	if (bgm_instance_)
		Play();
}

/**
* @brief ���[�v�Đ�(BGM)
*/
void SoundPlayer::Play() const {
	bgm_instance_->Play(true);
}

/**
* @brief �P���Đ�(SE)
*/
void SoundPlayer::PlayOneShot() const {
	sound_->Play();
}

/**
* @brief �w�肵���Đ����Ԃ̊ԍĐ�����
* @param deltaTime �t���[�����[�g�ɑ΂��Ă̈��̎���
* @return �Đ����I��������true�@�I�����Ă��Ȃ��Ȃ�false
*/
bool SoundPlayer::PlayOneShot(const float deltaTime) {
	if (timer_->NotYetCounted()) {
		PlayOneShot();
	}

	timer_->Update(deltaTime);

	return timer_->TimeOut();
}