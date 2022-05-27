/**
 * @file SoundPlayer.h
 * @brief 音素材の再生クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include"Base/pch.h"
#include"Base/dxtk.h"
#include"_Classes/_UI/_CountTimer/CountTimer.h"

/**
 * @enum SOUND_TYPE
 * 音素材の使用目的
 */
enum SOUND_TYPE { BGM, SE };

class SoundPlayer {
public:
	SoundPlayer();
	virtual ~SoundPlayer() {}

	void Initialize(std::wstring file_name, SOUND_TYPE sound_type, float playTime);
	void OnRestartSound();
	void Play() const;
	void PlayOneShot() const;
	bool PlayOneShot(const float deltaTime);

private:
	//! 音素材を保存する変数
	XAudio::SOUNDEFFECT sound_;

	//! SOUNDEFFECTをコントロールする変数
	XAudio::SOUNDEFFECTINSTANCE bgm_instance_;

	//! 再生時間変数
	std::unique_ptr<CountTimer> timer_;
};