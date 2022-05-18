/**
 * @file Fade.h
 * @brief フェード演出関連
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <algorithm>

namespace FADE {
	/**
	* @brief フェードインしたパラメーターを返す
	* @param num フェードインさせる値
	* @param max フェードインの最大値
	* @param speed フェードイン速度
	*/
	inline void In(float& num, float max, float speed) { num = std::min(num + speed, max); }

	/**
	* @brief フェードアウトしたパラメーターを返す
	* @param num フェードアウトさせる値
	* @param min フェードアウトの最小値
	* @param speed フェードアウト速度
	*/
	inline void Out(float& num, float min, float speed) { num = std::max(num - speed, min); }
}  //namespace FADE