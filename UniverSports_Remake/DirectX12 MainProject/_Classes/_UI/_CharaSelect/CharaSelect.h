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
#include "DontDestroyOnLoad.h"
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
	void Render();

	/**
	* @brief 決定状態を返す
	* @return 決定状態
	*/
	inline bool IsDecision() const { return isDecision_; }

private:
	void AutoSetter(int index, CHARATYPE type);
	void SelectToAvoidDupLicates(int index);
	bool haveSameValue(int index);

	std::unique_ptr<Choices>		choices_;		//! 選択クラス
	std::unique_ptr<SelectArrows>	ui_arrows_;		//! 矢印
	std::unique_ptr<SoundPlayer>	se_decision_;	//! 決定SE
	std::unique_ptr<SoundPlayer>	se_cancel_;		//! キャンセルSE
	std::unique_ptr<SoundPlayer>	se_warning_;	//! 警告SE
	
	bool isDecision_;	//! 決定フラグ
};