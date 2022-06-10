/**
 * @file BitCalculation.h
 * @brief ビット計算
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SpaceNumber.h"

namespace BitCalculation {
	//! 分割数
	const int NumberOfDivisions = 4;

	//! 分割する段階数
	const int DivisionLevel = 2;

	int BitSlide(int bit);
	int PointToMorton(DirectX::XMFLOAT2 pos);
	void MoverToMorton(DirectX::XMFLOAT2 m_pos, float radian, SpaceNumber& numbers);

	/**
	* @brief 空間レベルとレベル毎のインデックスからモートン符号を求める(等比級数)
	* @param Level 空間レベル
	* @param Index レベル毎のインデックス
	* @return モートン符号
	*/
	inline int GetIndex(int Level, int Index) {
		return (((std::pow(NumberOfDivisions, Level) - 1) / (NumberOfDivisions - 1)) + Index);
	}

}  //namespace BitCalculation