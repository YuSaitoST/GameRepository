/**
 * @file YsVirtualPad.h
 * @brief バーチャルパッド入力の基底クラス
 * @author 齋藤優宇
 * @date 2021/09/09
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "InputDevice.h"

/**
 * @enum PAD
 * 対応している入力
 */
enum class GM_VPAD {
	//! 右側の4種類のボタン
	P_X, P_Y, P_A, P_B,

	//! 十字キー
	P_UP, P_DOWN, P_LEFT, P_RIGHT,

	////! 左スティック
	//STICK_L_UP	, STICK_L_DOWN,
	//STICK_L_LEFT, STICK_L_RIGHT,
};


class YsVirtualPad : public InputDevice {
public:
	YsVirtualPad() {};
	virtual ~YsVirtualPad() {}

	virtual void accepts(int index) override {
		flag_ &= ~(1 << (int)GM_VPAD::P_UP);
		flag_ &= ~(1 << (int)GM_VPAD::P_DOWN);
		flag_ &= ~(1 << (int)GM_VPAD::P_LEFT);
		flag_ &= ~(1 << (int)GM_VPAD::P_RIGHT);

		direct_  = Vector2::Zero;
	}

	/**
	* @brief 入力された方向を返す
	* @return 入力された方向のベクトル
	*/
	virtual Vector2 get_direction(int id) override {
		direct_.Normalize();
		return direct_;
	}

	// 受け取った入力情報に合わせてデータを保存する
	virtual void set_inputflag(VPInput::VPInpSet vpInput) override {
		if (vpInput.INPUT_PATTERN == "B") {
			flag_ |= 1 << vpInput.BUTTON_ID;
			flag_ &= ~(~vpInput.PRESS << vpInput.BUTTON_ID);
		}
		else if (vpInput.INPUT_PATTERN == "S") {
			direct_.x = vpInput.X;
			direct_.y = vpInput.Y;

			flag_ |= (0.9f		<= direct_.y) << (int)GM_VPAD::P_UP;
			flag_ |= (direct_.y <= -0.9f	) << (int)GM_VPAD::P_DOWN;
			flag_ |= (direct_.x <= -0.9f	) << (int)GM_VPAD::P_LEFT;
			flag_ |= (0.9f		<= direct_.x) << (int)GM_VPAD::P_RIGHT;
		}
	}
};