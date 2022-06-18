/**
 * @file Serials.h
 * @brief 汎用的な計算処理
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#include <algorithm>

namespace StandardCalculation {

	/**
	* @brief 指定した範囲内に収める
	* @param num 範囲内に収めたい値
	* @param min 最小値
	* @param max 最大値
	*/
	template<typename Number> void Clamp(Number& num, Number min, Number max) {
		num = std::min(std::max(min, num), max);
	}

	/**
	* @brief 指定した範囲内でループさせる
	* @param num 範囲内でループさせたい値
	* @param min 最小値
	* @param max 最大値
	*/
	template<typename Number> void ValueLoop(Number& num, Number min, Number max) {
		if (num < min)
			num = max;

		if (max < num)
			num = min;
	}

	/**
	* @brief 指定した値の個数を返す
	* @param list 探索する配列
	* @param size 配列の要素数
	* @param findNum 探す値
	* @return 個数
	*/
	template<typename Number> int HowManyValuesIn(const Number* list, Number size, Number findNum) {
		int _count = 0;
		for (int _i = 0; _i < size; ++_i)
			_count += (int)(list[_i] == findNum);

		return _count;
	}

}  //namespace StandardCalculation