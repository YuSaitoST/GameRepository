/**
 * @file MyLife.h
 * @brief 残機クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <algorithm>

class MyLife {
public:
	MyLife(int life) : life_(life) {}
	virtual ~MyLife() {}

	/**
	* @brief ダメージ処理
	*/
	void TakeDamage() { life_ = std::max(0, life_ - 1); }

	/**
	* @brief 現在の残機数を返す
	* @return 残機数
	*/
	int NowLifePoint() const { return life_; }

private:
	//! 残機
	int life_;
};