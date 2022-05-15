/**
 * @file GamePadBase.h
 * @brief ゲームパッド入力の基底クラス
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
 * @enum PAD
 * 対応している入力
 */
enum PAD {
	//! 右側の4種類のボタン
	P_A, P_B, P_X, P_Y,

	//! 十字キー
	P_UP, P_DOWN, P_LEFT, P_RIGHT,

	//! 左スティック
	STICK_L_UP	, STICK_L_DOWN,
	STICK_L_LEFT, STICK_L_RIGHT,

	//! 右スティック
	STICK_R_UP	, STICK_R_DOWN,
	STICK_R_LEFT, STICK_R_RIGHT,

	//! 左右のショルダー
	SHOULDER_L	, SHOULDER_R,

	//! 左右のトリガー
	TRIGGER_L	, TRIGGER_R
};


class GamePadBase {
public:
	GamePadBase() : flag_(0) {};
	virtual ~GamePadBase() {}

	virtual void Accepts(int index) = 0;

	/**
	* @brief 指定したボタンの入力状態を返す
	* @param inputKey 入力状態を調べたいボタン
	* @return 入力されていればtrue　なければfalse
	*/
	inline bool OnOffKey(PAD inputKey) {
		return (flag_ & (1 << (int)inputKey));
	}

	/**
	* @brief 何かしらのボタン入力状態を返す
	* @return 入力されていればtrue　なければfalse
	*/
	inline bool AnyKey() {
		return (flag_ & 0xffffffff);
	}

	/**
	* @brief 入力された方向を返す
	* @return 入力された方向のベクトル
	*/
	inline Vector2 Direction() {
		if (flag_ & (1 << P_UP   )) direct_.y = -1;
		if (flag_ & (1 << P_DOWN )) direct_.y = 1;
		if (flag_ & (1 << P_LEFT )) direct_.x = -1;
		if (flag_ & (1 << P_RIGHT)) direct_.x = 1;
		direct_.Normalize();
		return direct_;
	}
	
protected:
	//! 入力状態をビットで保持する変数
	unsigned int flag_;

	//! 入力された方向を保持する変数
	Vector2 direct_;
};