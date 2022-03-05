#pragma once

#include"Base/pch.h"
#include"Base/dxtk.h"
#include"_Classes/_UI/_OriTimer/OriTimer.h"

using namespace DirectX;

enum SOUND_TYPE {
	BGM,
	SE
};

class SoundPlayer {
public:
	SoundPlayer();
	virtual ~SoundPlayer();

	void Initialize(std::wstring file_name, SOUND_TYPE sound_type);
	void Initialize(std::wstring file_name, SOUND_TYPE sound_type, int playTime);
	void OnRestartSound();
	void Update(const float deltaTime);

	void Play() const;
	void PlayOneShot() const;

	void AutoPlay(bool on) { autoPlay_ = true; }

	bool isFined() const { return timer_->TimeOut(); };

private:
	XAudio::SOUNDEFFECT sound_;
	XAudio::SOUNDEFFECTINSTANCE bgm_instance_;

	OriTimer* timer_;
	bool autoPlay_;
	bool isPlay_;
};