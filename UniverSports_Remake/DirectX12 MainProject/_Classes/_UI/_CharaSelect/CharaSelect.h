/**
 * @file CharaSelect.h
 * @brief キャラ選択クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_UI/_Choices/Choices.h"
#include "_Classes/_UI/_SelectArrows/SelectArrows.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"

class CharaSelect {
public:
	CharaSelect();
	virtual ~CharaSelect() {}

	CharaSelect(CharaSelect&&) = delete;
	CharaSelect& operator= (CharaSelect&&) = delete;

	CharaSelect(CharaSelect const&) = delete;
	CharaSelect& operator= (CharaSelect const&) = delete;

	void Initialize(int index);
	void LoadAssets(DX9::SPRITE right, DX9::SPRITE left);
	void Update(const float deltaTime, const int index);
	void Render(DX9::SPRITE& icon, DX9::SPRITE& decisions, DX9::SPRITE entry, int index);

	/**
	* @brief 決定状態を返す
	* @return 決定状態
	*/
	inline bool IsDecision() const { return isDecision_; }

private:
	void SelectToAvoidDupLicates(int index);
	bool haveSameValue(int index);

	const float INPUT_Y = 686.0f;
	const float ENTRY_Y = 585.0f;
	const float ARROW_Y = 600.0f;
	const float PICON_Y = 510.0f;

	const float TEAM_COL_X[4] = { 84.0f, 375.0f, 676.0f, 969.0f };
	const float TEAM_COL_Y = 493.5f;

	const float INPUT_X[4] = { 140.0f, 432.0f, 735.0f, 1029.0f };

	const float ENTRY_X[4] = { 108.0f, 400.0f, 702.0f, 991.0f };
	const float ARROW_L_X[4] = { 100.0f, 389.0f, 691.0f, 981.0f };
	const float ARROW_R_X[4] = { 283.0f, 572.0f, 874.0f, 1164.0f };
	const float PICON_X[4] = { ENTRY_X[0] - 5.0f, ENTRY_X[1] - 5.0f, ENTRY_X[2] - 5.0f, ENTRY_X[3] - 5.0f };

	//! 選択クラス
	std::unique_ptr<Choices> choices_;
	
	//! 矢印
	std::unique_ptr<SelectArrows> ui_arrows_;
	
	//! 決定SE
	std::unique_ptr<SoundPlayer> se_decision_;
	
	//! キャンセルSE
	std::unique_ptr<SoundPlayer> se_cancel_;
	
	//! 警告SE
	std::unique_ptr<SoundPlayer> se_warning_;
	
	//! 決定フラグ
	bool isDecision_;
};