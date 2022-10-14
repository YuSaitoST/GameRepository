/**
 * @file YsKeyboard.h
 * @brief キーボード入力クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "InputDevice.h"

/**
 * @enum KEY
 * 対応している入力
 */
enum class GM_KEY {
	//! A～Z
	A, B, C, D, E,
	F, G, H, I, J,
	K, L, M, N, O,
	P, Q, R, S, T,
	U, V, W, X, Y, Z,

	//! 十字キー
	UP, DOWN, LEFT, RIGHT,TAB
};

class YsKeyboard : public InputDevice {
public:
	YsKeyboard() {}
	virtual ~YsKeyboard() {}

	virtual Vector2 get_direction(int id) override { return get_direction(); }

	/**
	* @brief 入力状態を調べる
	*/
	virtual void accepts(int id) override {
		//桁上がり防止
		flag_	= 0;
		direct_ = Vector2::Zero;

		//各ビットに入力状態を入れる
		flag_ |= (bool)DXTK->KeyEvent->pressed.A	<< (int)GM_KEY::A;
		flag_ |= (bool)DXTK->KeyEvent->pressed.B	<< (int)GM_KEY::B;
		flag_ |= (bool)DXTK->KeyEvent->pressed.C	<< (int)GM_KEY::C;
		flag_ |= (bool)DXTK->KeyEvent->pressed.D	<< (int)GM_KEY::D;
		flag_ |= (bool)DXTK->KeyEvent->pressed.E	<< (int)GM_KEY::E;
		flag_ |= (bool)DXTK->KeyEvent->pressed.F	<< (int)GM_KEY::F;
		flag_ |= (bool)DXTK->KeyEvent->pressed.G	<< (int)GM_KEY::G;
		flag_ |= (bool)DXTK->KeyEvent->pressed.H	<< (int)GM_KEY::H;
		flag_ |= (bool)DXTK->KeyEvent->pressed.I	<< (int)GM_KEY::I;
		flag_ |= (bool)DXTK->KeyEvent->pressed.J	<< (int)GM_KEY::J;
		flag_ |= (bool)DXTK->KeyEvent->pressed.K	<< (int)GM_KEY::K;
		flag_ |= (bool)DXTK->KeyEvent->pressed.L	<< (int)GM_KEY::L;
		flag_ |= (bool)DXTK->KeyEvent->pressed.M	<< (int)GM_KEY::M;
		flag_ |= (bool)DXTK->KeyEvent->pressed.N	<< (int)GM_KEY::N;
		flag_ |= (bool)DXTK->KeyEvent->pressed.O	<< (int)GM_KEY::O;
		flag_ |= (bool)DXTK->KeyEvent->pressed.P	<< (int)GM_KEY::P;
		flag_ |= (bool)DXTK->KeyEvent->pressed.Q	<< (int)GM_KEY::Q;
		flag_ |= (bool)DXTK->KeyEvent->pressed.R	<< (int)GM_KEY::R;
		flag_ |= (bool)DXTK->KeyEvent->pressed.S	<< (int)GM_KEY::S;
		flag_ |= (bool)DXTK->KeyEvent->pressed.T	<< (int)GM_KEY::T;
		flag_ |= (bool)DXTK->KeyEvent->pressed.U	<< (int)GM_KEY::U;
		flag_ |= (bool)DXTK->KeyEvent->pressed.V	<< (int)GM_KEY::V;
		flag_ |= (bool)DXTK->KeyEvent->pressed.W	<< (int)GM_KEY::W;
		flag_ |= (bool)DXTK->KeyState->X			<< (int)GM_KEY::X;
		flag_ |= (bool)DXTK->KeyEvent->pressed.Y	<< (int)GM_KEY::Y;
		flag_ |= (bool)DXTK->KeyEvent->pressed.Z	<< (int)GM_KEY::Z;
		flag_ |= (bool)DXTK->KeyState->Up			<< (int)GM_KEY::UP;
		flag_ |= (bool)DXTK->KeyState->Down			<< (int)GM_KEY::DOWN;
		flag_ |= (bool)DXTK->KeyState->Left			<< (int)GM_KEY::LEFT;
		flag_ |= (bool)DXTK->KeyState->Right		<< (int)GM_KEY::RIGHT;
		flag_ |= (bool)DXTK->KeyEvent->pressed.Tab	<< (int)GM_KEY::TAB;
	}

	/**
	* @brief 入力した方向を返す
	* @return 入力された方向のベクトル
	*/
	virtual Vector2 get_direction() {
		if (flag_ & (1 << (int)GM_KEY::UP   )) direct_.y = 1;
		if (flag_ & (1 << (int)GM_KEY::DOWN )) direct_.y = -1;
		if (flag_ & (1 << (int)GM_KEY::LEFT )) direct_.x = -1;
		if (flag_ & (1 << (int)GM_KEY::RIGHT)) direct_.x = 1;
		direct_.Normalize();
		return direct_;
	}

	virtual void set_inputflag(VPInput::VPInpSet vpInput) override {}
};