/**
 * @file Cursor.h
 * @brief カーソルクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_UI/_Choices/Choices.h"

class Cursor {
public:
	Cursor();
	virtual ~Cursor() {}

	Cursor(Cursor&&) = delete;
	Cursor& operator= (Cursor&&) = delete;

	Cursor(Cursor const&) = delete;
	Cursor& operator= (Cursor const&) = delete;

	void Initialize(float posx, float posy, float moved);
	void LoadAsset(std::wstring file_name);
	bool Update(int choices, bool up, bool down);
	void Render(float alpha) const;

	/**
	 * @brief 現在選択している番号を返す
	 * @return 選択している番号
	*/
	inline int SelectNum() const { return choices_->SelectNum(); };

	/*
	* @brief 選択肢を指定する
	* @param 選択したい番号
	*/
	inline void SetSelectNum(int number) { choices_->SetSelectNum(number); }

private:
	//! 選択クラス
	std::unique_ptr<Choices> choices_;

	//! カーソルの画像
	DX9::SPRITE	sp_;

	//! カーソルの座標
	DirectX::SimpleMath::Vector3 pos_;

	//! 移動量
	float moved_;

	//! 開始Y座標
	float startPos_Y_;
};