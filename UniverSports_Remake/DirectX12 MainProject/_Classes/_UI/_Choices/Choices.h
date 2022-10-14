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
	virtual ~Choices() {};

	Choices(Choices&&) = delete;
	Choices& operator= (Choices&&) = delete;

	Choices(Choices const&) = delete;
	Choices& operator= (Choices const&) = delete;

	void Initialize();
	void Update(int choices, bool low, bool high);

	/**
	 * @brief 現在選択している番号を返す
	 * @return 選択している番号
	*/
	inline int SelectNum() const { return isSelected_; };

	/*
	* @brifef 選択肢を指定する
	* @param 選択したい番号
	*/
	inline void SetSelectNum(int number) { isSelected_ = number; }

	/**
	 * @brief 次の入力を受け付けられるようにする
	 * @param on 次の選択が可能かの真偽
	*/
	inline void NextSelectOn(const bool on) { putCount_ = (int)on; }

private:
	//! 入力時のSE
	std::unique_ptr<SoundPlayer> se_choice_;
	
	//! 現在選択している番号
	int isSelected_;

	//! 入力回数
	int putCount_;
};