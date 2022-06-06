/**
 * @file CellList.h
 * @brief 空間リストクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Object/ObjectBase.h"

// 前方宣言
class Cell;

// 空間リストクラス
class CellList {
public:
	CellList();
	virtual ~CellList();

	void PushList(Cell* cp);
	ObjectBase* GetCollision(int index, ObjectBase* m);

private:
	//! 分割レベルの最大値
	const int N = 2;

	//! 線形空間リスト
	Cell* cpList_;

};