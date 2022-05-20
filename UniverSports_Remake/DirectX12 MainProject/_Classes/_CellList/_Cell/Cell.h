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
#include "_Classes/_BitCalculation/BitCalculation.h"

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

	//" 双方向リスト(自分の前後の空間を入れる)
	Cell* prev_;
	Cell* next_;

	//! 空間に所属する物体
	ObjectBase* mp_;

	//! 空間番号
	SpaceNumber numbers_;

private:
	ObjectBase* UpperSearch();		  // 上位探索
	ObjectBase* LowerSearch(int nr);  // 下位探索
};