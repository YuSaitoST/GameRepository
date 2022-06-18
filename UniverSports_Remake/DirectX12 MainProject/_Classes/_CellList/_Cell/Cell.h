/**
 * @file Serials.h
 * @brief 空間クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

  //------------------------------------------------------------------------------
  //	インクルードファイル
  //------------------------------------------------------------------------------
#include "_Classes/_CellList/_BitCalculation/BitCalculation.h"

//前方宣言
class ObjectBase;

class Cell {
public:
	Cell();
	Cell(ObjectBase* m);
	virtual ~Cell();

	void UpdateToMorton();
	void Remove();
	ObjectBase* GetCollision();

	//! 双方向リスト
	Cell* prev_;
	Cell* next_;

	//! 空間に所属する物体
	ObjectBase* mp_;

	//! 空間番号
	SpaceNumber numbers_;

private:
	ObjectBase* UpperSearch();
	ObjectBase* LowerSearch(int nr);
};