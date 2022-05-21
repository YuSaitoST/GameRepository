/**
 * @file MyLife.h
 * @brief �c�@�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <algorithm>

class MyLife {
public:
	MyLife(int life) : life_(life) {}
	virtual ~MyLife() {}

	/**
	* @brief �_���[�W����
	*/
	void TakeDamage() { life_ = std::max(0, life_ - 1); }

	/**
	* @brief ���݂̎c�@����Ԃ�
	* @return �c�@��
	*/
	int NowLifePoint() const { return life_; }

private:
	//! �c�@
	int life_;
};