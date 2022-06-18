/**
 * @file Serials.h
 * @brief �ėp�I�Ȍv�Z����
 * @author �V���D�F
 * @date 2021/05/14
 */

#include <algorithm>

namespace StandardCalculation {

	/**
	* @brief �w�肵���͈͓��Ɏ��߂�
	* @param num �͈͓��Ɏ��߂����l
	* @param min �ŏ��l
	* @param max �ő�l
	*/
	template<typename Number> void Clamp(Number& num, Number min, Number max) {
		num = std::min(std::max(min, num), max);
	}

	/**
	* @brief �w�肵���͈͓��Ń��[�v������
	* @param num �͈͓��Ń��[�v���������l
	* @param min �ŏ��l
	* @param max �ő�l
	*/
	template<typename Number> void ValueLoop(Number& num, Number min, Number max) {
		if (num < min)
			num = max;

		if (max < num)
			num = min;
	}

	/**
	* @brief �w�肵���l�̌���Ԃ�
	* @param list �T������z��
	* @param size �z��̗v�f��
	* @param findNum �T���l
	* @return ��
	*/
	template<typename Number> int HowManyValuesIn(const Number* list, Number size, Number findNum) {
		int _count = 0;
		for (int _i = 0; _i < size; ++_i)
			_count += (int)(list[_i] == findNum);

		return _count;
	}

}  //namespace StandardCalculation