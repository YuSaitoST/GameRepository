/**
 * @file SelectedRender.h
 * @brief キャラクター選択状態の描画クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "UserInputRender.h"

class SelectedRender : public UserInputRender {
public:
	SelectedRender() : sp_cancel_(DX9::SPRITE{}), sp_entry_(DX9::SPRITE{}) {}
	virtual ~SelectedRender() {}

	virtual void LoadAssets() override;
	virtual void Render(int playerID) override;

private:
	DX9::SPRITE sp_cancel_;	//! キャンセル
	DX9::SPRITE sp_entry_;	//! エントリー
};