/**
 * @file GamePadChecker.h
 * @brief ゲームパッドの入力を総括するクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "GamePadEvent.h"
#include "GamePadState.h"


//マクロ
#define N_PAD DXTK_GAMEPAD

class GamePadChecker {
public:
	GamePadChecker() {}
	virtual ~GamePadChecker() {}

	/**
	* @brief 入力状態を調べる
	* @param index 接続されているゲームパッドの番号
	*/
	void Accepts(int index) {
		inpEvent_[index].Accepts(index);
		inpState_[index].Accepts(index);
	}

	/**
	* @brief 指定したゲームパッドの、指定したボタンの単発入力状態を返す
	* @param index ゲームパッドの番号
	* @param inputKey 入力状態を調べたいボタン
	* @return 入力されていればtrue　なければfalse
	*/
	bool EventOnOffKey(int index, PAD inputKey) {
		return inpEvent_[index].OnOffKey(inputKey);
	}

	/**
	* @brief 何かしらのボタンの単発入力状態を返す
	* @param index ゲームパッドの番号
	* @return 入力されていればtrue　なければfalse
	*/
	bool EventAnyKey(int index) {
		return inpEvent_[index].AnyKey();
	}

	/**
	* @brief 十字キーの単発入力した方向を返す
	* @param index ゲームパッドの番号
	* @return 入力された方向のベクトル
	*/
	Vector2 EventDirection4(int index) {
		return inpEvent_[index].Direction();
	}

	/**
	* @brief 指定したボタンの長押し入力状態を返す
	* @param indes ゲームパッドの番号
	* @param inputKey 入力状態を調べたいボタン
	* @return 入力されていればtrue　なければfalse
	*/
	bool StateOnOffKey(int index, PAD inputKey) {
		return inpState_[index].OnOffKey(inputKey);
	}

	/**
	* @brief 何かしらボタンの長押し入力状態を返す
	* @param index ゲームパッドの番号
	* @return 入力されていればtrue　なければfalse
	*/
	bool StateAnyKey(int index) {
		return inpState_[index].AnyKey();
	}

	/**
	* @brief 十字キーの長押し入力した方向を返す
	* @param index ゲームパッドの番号
	* @return 入力された方向を返す
	*/
	Vector2 StateDirection4(int index) {
		return inpState_[index].Direction();
	}

	/**
	* @brief 左スティックの長押し入力した方向を返す
	* @param index ゲームパッドの番号
	* @return 入力された方向を返す
	*/
	Vector2 LeftStateDirection360(int index) {
		return inpState_[index].LeftDirection();
	}

	/**
	* @brief 右スティックの長押し入力した方向を返す
	* @param index ゲームパッドの番号
	* @return 入力された方向を返す
	*/
	Vector2 RightStateDirection360(int index) {
		return inpState_[index].RightDirection();
	}

	/**
	* @brief 左トリガーの入力値を返す
	* @param index ゲームパッドの番号
	* @return 入力値(0～1)
	*/
	float LeftTrigger(int index) {
		return inpState_[index].LeftTrigger();
	}

	/**
	* @brief 右トリガーの入力値を返す
	* @param index ゲームパッドの番号
	* @return 入力値(0～1)
	*/
	float RightTrigger(int index) {
		return inpState_[index].RightTrigger();
	}

private:
	//! ゲームパッドの単発入力変数、使うゲームパッドの数用意
	GamePadEvent inpEvent_[N_PAD];

	//!< ゲームパッドの長押し入力変数、使うゲームパッドの数用意
	GamePadState inpState_[N_PAD];
};