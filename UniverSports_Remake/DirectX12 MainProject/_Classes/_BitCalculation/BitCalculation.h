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
	int BitSlide(int bit);
	int PointToMorton(DirectX::XMFLOAT2 pos);
	int GetIndex(int Level, int Index);
	void MoverToMorton(DirectX::XMFLOAT2 m_pos, float radian, SpaceNumber& numbers);

	//! 分割数
	const int NumberOfDivisions = 4;

	//! 分割する段階数
	const int DivisionLevel = 2;

}  //namespace BitCalculation