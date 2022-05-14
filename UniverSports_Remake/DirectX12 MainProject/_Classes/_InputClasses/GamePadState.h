/**
 * @file GamePadState.h
 * @brief ゲームパッドの長押し入力クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "GamePadBase.h"

class GamePadState final : public GamePadBase {
public:
	GamePadState() :direct_L_(Vector2::Zero), direct_R_(Vector2::Zero), n_Ltrg_(0), n_Rtrg_(0) {};
	virtual ~GamePadState() {}

	virtual void Accepts(int index) override;

	/**
	* @brief 左スティックの入力方向を返す
	* @return 入力された方向のベクトル
	*/
	Vector2 LeftDirection() {
		direct_L_.Normalize();
		return direct_L_;
	}

	/**
	* @brief 右スティックの入力方向を返す
	* @return 入力された方向のベクトル
	*/
	Vector2 RightDirection() {
		direct_R_.Normalize();
		return direct_R_; 
	}

	/**
	* @brief 左トリガーの入力値を返す
	* @return 入力値(0～1)
	*/
	float LeftTrigger() { 
		return n_Ltrg_; 
	}

	/**
	* @brief 右トリガーの入力値を返す
	* @return 入力値(0～1)
	*/
	float RightTrigger() {
		return n_Rtrg_;
	}

private:
	Vector2 direct_L_;		//!< 左スティックの入力方向
	Vector2 direct_R_;		//!< 右スティックの入力方向
	float n_Ltrg_, n_Rtrg_;	//!< トリガーの入力値
};