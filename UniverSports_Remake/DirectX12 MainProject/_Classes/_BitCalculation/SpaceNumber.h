/**
 * @file SpaceNumber.h
 * @brief 空間分割で用いる番号の構造体
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

struct SpaceNumber {
	SpaceNumber operator =(int n) {
		SpaceNumber num;
		num.Level_		= n;
		num.LsIndex_	= n;
		num.MsIndex_	= n;
		return num;
	}

	//! 空間レベル
	int Level_;

	//! 各レベルでのインデックス
	int LsIndex_;

	//! 線形四分木におけるインデックス
	int MsIndex_;
};