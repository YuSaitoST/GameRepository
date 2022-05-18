/**
 * @file Fade.h
 * @brief �t�F�[�h���o�֘A
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <algorithm>

namespace FADE {
	/**
	* @brief �t�F�[�h�C�������p�����[�^�[��Ԃ�
	* @param num �t�F�[�h�C��������l
	* @param max �t�F�[�h�C���̍ő�l
	* @param speed �t�F�[�h�C�����x
	*/
	inline void In(float& num, float max, float speed) { num = std::min(num + speed, max); }

	/**
	* @brief �t�F�[�h�A�E�g�����p�����[�^�[��Ԃ�
	* @param num �t�F�[�h�A�E�g������l
	* @param min �t�F�[�h�A�E�g�̍ŏ��l
	* @param speed �t�F�[�h�A�E�g���x
	*/
	inline void Out(float& num, float min, float speed) { num = std::max(num - speed, min); }
}  //namespace FADE