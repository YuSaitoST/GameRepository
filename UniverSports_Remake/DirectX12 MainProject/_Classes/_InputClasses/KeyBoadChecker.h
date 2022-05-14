/**
 * @file KeyBoadChecker.h
 * @brief キーボードの入力を総括するクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "KeyBoadEvent.h"
#include "KeyBoadState.h"

class KeyBoadChecker {
public:
	KeyBoadChecker() {}
	virtual ~KeyBoadChecker() {}

	/**
	* @brief 入力状態を調べる
	*/
	void Accepts(){
		inpEvent_.Accepts();
		inpState_.Accepts();
	}

	/**
	* @brief 指定したボタンの単発入力状態を返す
	* @param inputKey 入力状態を調べたいボタン
	* @return 入力されていればtrue　なければfalse
	*/
	bool EventOnOffKey(KEY inputKey){
		return inpEvent_.OnOffKey(inputKey);
	}

	/**
	* @brief 何かしらボタンの単発入力状態を返す
	* @return 入力されていればtrue　なければfalse
	*/
	bool EventAnyKey(){
		return inpEvent_.AnyKey();
	}

	/**
	* @brief 単発入力した方向を返す
	* @return 入力された方向のベクトル
	*/
	Vector2 EventDirection(){
		return inpEvent_.Direction();
	}
	
	/**
	* @brief 指定したボタンの長押し入力状態を返す
	* @param inputKey 入力状態を調べたいボタン
	* @return 入力されていればtrue　なければfalse
	*/
	bool StateOnOffKey(KEY inputKey){
		return inpState_.OnOffKey(inputKey);
	}

	/**
	* @brief 何かしらボタンの長押し入力状態を返す
	* @return 入力されていればtrue　なければfalse
	*/
	bool StateAnyKey(){
		return inpState_.AnyKey();
	}

	/**
	* @brief 長押し入力した方向を返す
	* @return 入力された方向のベクトル
	*/
	Vector2 StateDirection(){
		return inpState_.Direction();
	}

private:
	//! キーボードの単発入力変数
	KeyBoadEvent inpEvent_;

	//! キーボードの長押し入力変数
	KeyBoadState inpState_;
};