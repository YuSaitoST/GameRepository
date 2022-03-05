#include"SoundPlayer.h"

SoundPlayer::SoundPlayer() {
	sound_			= nullptr;
	bgm_instance_	= nullptr;
	timer_			= nullptr;
	autoPlay_		= false;
	isPlay_			= false;
}

SoundPlayer::~SoundPlayer() {
	delete timer_;
}

void SoundPlayer::Initialize(std::wstring file_name, SOUND_TYPE sound_type) {
	sound_			= XAudio::CreateSoundEffect(DXTK->AudioEngine, file_name.c_str());
	bgm_instance_	= (sound_type == SOUND_TYPE::BGM) ? sound_->CreateInstance() : XAudio::SOUNDEFFECTINSTANCE{};
}

void SoundPlayer::Initialize(std::wstring file_name, SOUND_TYPE sound_type, int playTime) {
	sound_			= XAudio::CreateSoundEffect(DXTK->AudioEngine, file_name.c_str());
	bgm_instance_	= (sound_type == SOUND_TYPE::BGM) ? sound_->CreateInstance() : XAudio::SOUNDEFFECTINSTANCE{};
	timer_			= new OriTimer(playTime);
}

void SoundPlayer::OnRestartSound() {
	if (bgm_instance_)
		Play();
}

void SoundPlayer::Update(const float deltaTime) {
	if (autoPlay_) {
		if (!isPlay_) {
			PlayOneShot();
			isPlay_ = false;
			autoPlay_ = false;
		}
	}

	timer_->Update(deltaTime);
}

void SoundPlayer::Play() const {
	bgm_instance_->Play(true);
}

void SoundPlayer::PlayOneShot() const {
	sound_->Play();
}