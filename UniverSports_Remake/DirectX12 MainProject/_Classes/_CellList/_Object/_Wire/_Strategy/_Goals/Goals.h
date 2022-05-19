/**
 * @file Goals.h
 * @brief ワイヤーのゴールとしての振る舞いクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Wire/_Strategy/WireStrategy.h"

class Goals : public WireStrategy {
public:
	Goals() {}
	virtual ~Goals() {}

	virtual void Update(ObjWire* wire);

private:

};