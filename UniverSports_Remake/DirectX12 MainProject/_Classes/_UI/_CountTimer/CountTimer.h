/**
 * @file CountTimer.h
 * @brief �^�C�}�[�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <algorithm>

class CountTimer {
public:
	CountTimer(float countTime) : max_(countTime), time_(countTime) {}
	virtual ~CountTimer() {}

	inline void Update(const float deltaTime) { time_ = std::max(0.0f, time_ - deltaTime); }

	/**
	* @brief �^�C�}�[�����Z�b�g����
	*/
	inline void Reset() { time_ = max_; }

	/**
	* @brief ���̌o�ߎ��Ԃ�Ԃ�
	* @return �o�ߎ���
	*/
	inline float NowTime() const { return time_; }

	/**
	* @brief �J�E���g���J�n��������Ԃ�
	* @return �J�E���g�J�n�O�Ȃ�true�@�J�E���g���Ȃ�false
	*/
	inline bool NotYetCounted() const { return (time_ == max_); }

	/**
	* @brief �^�C�}�[���I����������Ԃ�
	* @return �^�C�}�[�̏I�����
	*/
	inline bool TimeOut() const { return (time_ <= 0.0f); }

private:
	//! �^�C�}�[�̍ő�l
	float max_;

	//! �o�ߎ���
	float time_;
};