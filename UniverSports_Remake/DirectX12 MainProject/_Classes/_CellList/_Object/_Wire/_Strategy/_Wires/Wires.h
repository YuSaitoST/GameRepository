/**
 * @file Wires.h
 * @brief ワイヤーのワイヤーとしての振る舞いクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Wire/_Strategy/WireStrategy.h"

class Wires : public WireStrategy {
public:
	Wires() {}
	virtual ~Wires() {}

	/**
	 * @brief ワイヤーの振る舞い(処理なし)
	 * @param wire ワイヤークラス自身
	*/
	virtual void Update(ObjWire* wire) {}
};