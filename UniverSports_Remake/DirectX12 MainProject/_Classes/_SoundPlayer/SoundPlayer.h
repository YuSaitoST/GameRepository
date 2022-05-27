/**
 * @file SoundPlayer.h
 * @brief ���f�ނ̍Đ��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include"Base/pch.h"
#include"Base/dxtk.h"
#include"_Classes/_UI/_CountTimer/CountTimer.h"

/**
 * @enum SOUND_TYPE
 * ���f�ނ̎g�p�ړI
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
	//! ���f�ނ�ۑ�����ϐ�
	XAudio::SOUNDEFFECT sound_;

	//! SOUNDEFFECT���R���g���[������ϐ�
	XAudio::SOUNDEFFECTINSTANCE bgm_instance_;

	//! �Đ����ԕϐ�
	std::unique_ptr<CountTimer> timer_;
};