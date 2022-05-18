/**
 * @file Serials.h
 * @brief 連番素材に関するパラメーター
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
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
	* @brief 表示させる範囲の左側の値を求める
	* @param number 表示させたい番号
	* @param numbersMax 連番の最大値
	* @param wight 連番の要素1つの幅
	* @return 表示範囲の左x値
	*/
	inline float GetRectX(int number, int numbersMax, int wight) { return std::min(number, numbersMax) * wight; }
}  //namespace SERIALS