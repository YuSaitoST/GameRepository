#include"SoundPlayer.h"

SoundPlayer::SoundPlayer() : sound_(XAudio::SOUNDEFFECT()), bgm_instance_(XAudio::SOUNDEFFECTINSTANCE()) {
	timer_			= nullptr;
}

SoundPlayer::~SoundPlayer() {
	delete timer_;
}

/**
* @brief 初期化
*/
void SoundPlayer::Initialize(std::wstring file_name, SOUND_TYPE sound_type, float playTime) {
	sound_			= XAudio::CreateSoundEffect(DXTK->AudioEngine, file_name.c_str());
	bgm_instance_	= (sound_type == SOUND_TYPE::BGM) ? sound_->CreateInstance() : nullptr;
	timer_			= new CountTimer(playTime);
}

/**
* @brief ヘッドホンの抜き差し等によるデバイスリセット時に再生し直す
*/
void SoundPlayer::OnRestartSound() {
	if (bgm_instance_)
		Play();
}

/**
* @brief ループ再生(BGM)
*/
void SoundPlayer::Play() const {
	bgm_instance_->Play(true);
}

/**
* @brief 単発再生(SE)
*/
void SoundPlayer::PlayOneShot() const {
	sound_->Play();
}

/**
* @brief 指定した再生時間の間再生する
* @param deltaTime フレームレートに対しての一定の時間
* @return 再生が終了したらtrue　終了していないならfalse
*/
bool SoundPlayer::PlayOneShot(const float deltaTime) {
	if (timer_->NotYetCounted()) {
		PlayOneShot();
	}

	timer_->Update(deltaTime);

	return timer_->TimeOut();
}