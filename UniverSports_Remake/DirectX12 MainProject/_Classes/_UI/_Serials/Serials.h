/**
 * @file Serials.h
 * @brief �A�ԗp����
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <algorithm>

namespace SERIALS {
	/**
	* @brief �\��������͈͂̍����̒l�����߂�
	* @param number �\�����������ԍ�
	* @param numbersMax �A�Ԃ̍ő�l
	* @param wight �A�Ԃ̗v�f1�̕�
	* @return �\���͈͂̍�x�l
	*/
	inline float GetRectX(int number, int numbersMax, int wight) { return std::min(number, numbersMax) * wight; }

}  //namespace SERIALS