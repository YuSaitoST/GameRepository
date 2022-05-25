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
	virtual ~Cursor();

	Cursor(Cursor&&) = delete;
	Cursor& operator= (Cursor&&) = delete;

	Cursor(Cursor const&) = delete;
	Cursor& operator= (Cursor const&) = delete;

	void Initialize();
	void LoadAsset(std::wstring file_name);
	void Update(int choices);
	void Render(float alpha) const;

	/**
	 * @brief 現在選択している番号を返す
	 * @return 選択している番号
	*/
	int SelectNum() const { return choices_->SelectNum(); };

private:
	const float MOVE_Y	= 102.0f;
	const float POS_X	= 360.0f;
	const float POS_Y	= 415.0f;

private:
	//! 選択クラス
	Choices* choices_;

	//! カーソルの画像
	DX9::SPRITE	sp_;

	//! カーソルの座標
	DirectX::SimpleMath::Vector3 pos_;
};