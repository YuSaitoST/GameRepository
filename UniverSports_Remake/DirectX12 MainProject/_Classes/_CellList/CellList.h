#pragma once

#include "_Object/ObjectBase.h"
#include "_Cell/Cell.h"

// 空間リストクラス
class CellList {
public:
	CellList();
	virtual ~CellList();

	void PushList(Cell* cp);  // リストに追加
	ObjectBase* GetCollision(int index, ObjectBase* m);  // 衝突判定	

private:
	const int N = 2;  // 分割レベルの最大
	Cell* cpList_;  // 線形空間リスト(CellをまとめるList)
};