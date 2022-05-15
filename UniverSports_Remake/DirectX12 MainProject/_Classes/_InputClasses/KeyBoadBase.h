/**
 * @file KeyBoadBase.h
 * @brief キーボード入力の基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX::SimpleMath;

/**
 * @enum KEY
 * 対応している入力
 */
enum KEY {
	//! A～Z
	A, B, C, D, E,
	F, G, H, I, J,
	K, L, M, N, O,
	P, Q, R, S, T,
	U, V, W, X, Y, Z,

	//! 十字キー
	UP, DOWN, LEFT, RIGHT,TAB
};

class KeyBoadBase {
public:
	KeyBoadBase() : flag_(0) {}
	virtual ~KeyBoadBase() {}

	virtual void Accepts() = 0;

	/**
	* @brief 指定したボタンの入力状態を返す
	* @param inputKey 入力状態を調べたいボタン
	* @return 入力されていればtrue　なければfalse
	*/
	inline bool OnOffKey(KEY inputKey) {
		return (flag_ & (1 << (int)inputKey));
	}

	/**
	* @brief 何かしらボタンの入力状態を返す
	* @return 入力されていればtrue　なければfalse
	*/
	inline bool AnyKey() {
		return (flag_ & 0xffffffff);
	}

	/**
	* @brief 入力した方向を返す
	* @return 入力された方向のベクトル
	*/
	inline Vector2 Direction() {
		if (flag_ & (1 << UP   )) direct_.y = 1;
		if (flag_ & (1 << DOWN )) direct_.y = -1;
		if (flag_ & (1 << LEFT )) direct_.x = -1;
		if (flag_ & (1 << RIGHT)) direct_.x = 1;
		direct_.Normalize();
		return direct_;
	}

protected:
	//! 入力状態を保持する
	unsigned int flag_;

	//! 入力した方向を保持する
	Vector2 direct_;

private:
	//! A～Zの文字数
	const int CHARA = 26;
};