/**
 * @file Serials.h
 * @brief 連番用処理
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <algorithm>

namespace SERIALS {
	/**
	* @brief 表示させる範囲の左側の値を求める
	* @param number 表示させたい番号
	* @param numbersMax 連番の最大値
	* @param wight 連番の要素1つの幅
	* @return 表示範囲の左x値
	*/
	inline float GetRectX(int number, int numbersMax, int wight) { return std::min(number, numbersMax) * wight; }

}  //namespace SERIALS