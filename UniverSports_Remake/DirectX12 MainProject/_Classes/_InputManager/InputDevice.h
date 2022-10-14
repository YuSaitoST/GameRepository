/**
 * @file InputDevice.h
 * @brief 入力デバイス基底クラス
 * @author 齋藤優宇
 * @date 2021/08/05
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_VPServer/VPInputData.h"

using namespace DirectX::SimpleMath;

class InputDevice {
public:
	InputDevice() : flag_(0), direct_(DirectX::XMFLOAT2()) {}
	virtual ~InputDevice() {}

	virtual void accepts(int id) = 0;
	virtual Vector2 get_direction(int id) = 0;
	virtual void set_inputflag(VPInput::VPInpSet vpInput) = 0;

	/**
	* @brief 何かしらのボタン入力状態を返す
	* @return 入力されていればtrue　なければfalse
	*/
	inline bool get_anykey() {
		return flag_ != 0;
	}

	/**
	* @brief 指定したボタンの入力状態を返す
	* @param KeyID 入力状態を調べたいボタン
	* @return 入力されていればtrue　なければfalse
	*/
	inline bool get_key(int keyID) {
		return (flag_ & (1 << keyID));
	}

protected:
	//! 入力状態をビットで保持する変数
	unsigned int flag_;

	//! 入力された方向を保持する変数
	Vector2 direct_;
};