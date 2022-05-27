/**
 * @file Serials.h
 * @brief �ėp�I�Ȍv�Z
 * @author �V���D�F
 * @date 2021/05/14
 */

namespace StandardCalculation {

	template<typename Number> void ValueLoop(Number& num, Number min, Number max);

}  //namespace StandardCalculation

template<typename Number>
void StandardCalculation::ValueLoop(Number& num, Number min, Number max) {
	if (num < min)
		num = max;

	if (max < num)
		num = min;
}
