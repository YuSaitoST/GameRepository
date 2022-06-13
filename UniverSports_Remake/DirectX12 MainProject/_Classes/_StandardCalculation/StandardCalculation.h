/**
 * @file Serials.h
 * @brief ”Ä—p“I‚ÈŒvZˆ—
 * @author âV“¡—D‰F
 * @date 2021/05/14
 */

namespace StandardCalculation {

	template<typename Number> void ValueLoop(Number& num, Number min, Number max) {
		if (num < min)
			num = max;

		if (max < num)
			num = min;
	}

	template<typename Number> int HowManyValuesIn(const Number* list, Number size, Number findNum) {
		int _count = 0;
		for (int _i = 0; _i < size; ++_i)
			_count += (int)(list[_i] == findNum);

		return _count;
	}

}  //namespace StandardCalculation