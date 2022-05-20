/**
 * @file Choices.h
 * @brief 選択クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_SoundPlayer/SoundPlayer.h"

class Choices {
public:
	Choices();
	virtual ~Choices() { delete se_choice_; };

	void Initialize();
	void Update(int choices, bool low, bool high);

	/**
	 * @brief 現在選択している番号を返す
	 * @return 選択している番号
	*/
	int SelectNum() const { return isSelected; };

	/**
	 * @brief 次の入力を受け付けられるようにする
	 * @param on 次の選択が可能かの真偽
	*/
	void NextSelectOn(const bool on) { putCount_ = (int)on; }

private:
	//! 入力時のSE
	SoundPlayer* se_choice_;
	
	//! 現在選択している番号
	int isSelected;

	//! 入力回数
	int putCount_;
};