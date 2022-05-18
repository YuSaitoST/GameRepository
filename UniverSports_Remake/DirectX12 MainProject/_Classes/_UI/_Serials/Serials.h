/**
 * @file Serials.h
 * @brief �A�ԑf�ނɊւ���p�����[�^�[
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <algorithm>

namespace SERIALS {
	namespace NUMBER {
		const int		POS_X	= 360;
		const int		POS_Y	= 462;
		const int		RECT_X	= 50;
		const int		RECT_Y	= 75;
		const int		MAX		= 9;
	}  //namespace NUMBER
	namespace PLAYER {
		const int		POS_X	= 115;
		const int		POS_Y	= 250;
		const int		RECT_X	= 270;
		const int		RECT_Y	= 135;
		const int		MAX		= 3;
	}  //namespace PLAYER

	/**
	* @brief �\��������͈͂̍����̒l�����߂�
	* @param number �\�����������ԍ�
	* @param numbersMax �A�Ԃ̍ő�l
	* @param wight �A�Ԃ̗v�f1�̕�
	* @return �\���͈͂̍�x�l
	*/
	inline float GetRectX(int number, int numbersMax, int wight) { return std::min(number, numbersMax) * wight; }
}  //namespace SERIALS