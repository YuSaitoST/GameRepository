/**
 * @file YsGamePad.h
 * @brief ゲームパッド入力の基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
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
enum class GM_PAD {
	//! 右側の4種類のボタン
	P_A, P_B, P_X, P_Y,

	//! 十字キー
	P_UP, P_DOWN, P_LEFT, P_RIGHT,

	////! 左スティック
	//STICK_L_UP	, STICK_L_DOWN,
	//STICK_L_LEFT, STICK_L_RIGHT,

	////! 右スティック
	//STICK_R_UP	, STICK_R_DOWN,
	//STICK_R_LEFT, STICK_R_RIGHT,

	////! 左右のショルダー
	//SHOULDER_L	, SHOULDER_R,

	////! 左右のトリガー
	//TRIGGER_L	, TRIGGER_R
};


class YsGamePad : public InputDevice {
public:
	YsGamePad() {};
	virtual ~YsGamePad() {}

	/**
	* @brief 入力状態を調べる
	* @param index ゲームパッドの番号
	*/
	virtual void accepts(int index) override{
		//桁上がり防止
		flag_ = 0;

		//各ビットに入力状態を入れる
		flag_ |= (bool)DXTK->GamePadEvent[index].a			<< (int)GM_PAD::P_A;
		flag_ |= (bool)DXTK->GamePadEvent[index].b			<< (int)GM_PAD::P_B;
		flag_ |= (bool)DXTK->GamePadEvent[index].x			<< (int)GM_PAD::P_X;
		flag_ |= (bool)DXTK->GamePadEvent[index].y			<< (int)GM_PAD::P_Y;
		flag_ |= (bool)DXTK->GamePadEvent[index].dpadUp		<< (int)GM_PAD::P_UP;
		flag_ |= (bool)DXTK->GamePadEvent[index].dpadDown	<< (int)GM_PAD::P_DOWN;
		flag_ |= (bool)DXTK->GamePadEvent[index].dpadLeft	<< (int)GM_PAD::P_LEFT;
		flag_ |= (bool)DXTK->GamePadEvent[index].dpadRight	<< (int)GM_PAD::P_RIGHT;

		//0.0～1.0で取る入力
		direct_.x = DXTK->GamePadState[index].thumbSticks.leftX;
		direct_.y = DXTK->GamePadState[index].thumbSticks.leftY;
	}

	/**
	* @brief 入力された方向を返す
	* @return 入力された方向のベクトル
	*/
	virtual Vector2 get_direction(int id) {
		direct_.Normalize();
		return direct_;
	}

	virtual void set_inputflag(VPInput::VPInpSet vpInput) override {}
};