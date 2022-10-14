/**
 * @file ConfigDisplay.h
 * @brief タイトルの通常画面表示クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "DisplayBase.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"
#include "_Classes/_UI/_SelectArrows/SelectArrows.h"
#include "_Classes/_UI/_Choices/Choices.h"
#include "_Configs/ConfigState.h"

class ConfigDisplay final : public DisplayBase {
public:
	ConfigDisplay();
	virtual ~ConfigDisplay() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual NextScene Update(const float deltaTime) override;
	virtual void Render() override;
	virtual void Reset() override {}
	virtual DISPLAYMODE IsChange() override;
	virtual void ReDisplayInitialize() override;

	inline void UpdateSelectSystem(int systemID) { selectSystemID_[selectPlID_] = (InputSystem)systemID; }
	inline void BackToTheTitle() { backToTheTitle_ = true; }
	inline void ChangeSelect(int id) { selectID_ = id; }
	inline void SelectPlayer(int id) { selectPlID_ = id; }
	void DecisionInpSystem();
	void CancelSystemSelect();

	inline int GetSelectPlayer() const { return selectPlID_; }
	inline void SE_PlayDecision() { se_decision_->PlayOneShot(); }
	inline void SE_PlayCancel() { se_cancel_->PlayOneShot(); }

private:
	const int PlayerCount = 4;

	const int POS_PlayerID_X = 180;
	const int POS_Operates_X = 460;
	const int POS_AllTexts_Y[4] = { 135,220,305,395 };
	const int IP_POS_X = 880;
	const int IP_POS_Y = 150;

	const std::wstring TXT_SPACE		= L" ";
	const std::wstring TXT_PlayerID_[4] = { L"P1", L"P2", L"P3", L"P4" };
	const std::wstring TXT_Operates_[4] = { L"Keyboard", L"GamePad", L"VirtualPad", L"COM" };

private:
	std::vector<std::unique_ptr<ConfigState>>	configSelector_;
	std::unique_ptr<SoundPlayer>				se_decision_;		//! 決定SE
	std::unique_ptr<SoundPlayer>				se_cancel_;			//! キャンセルSE

	DX9::SPRITEFONT	font_selects_;
	DX9::SPRITEFONT font_message_;
	DX9::SPRITE		sp_bg_;

	InputSystem selectSystemID_[4];	// 各プレイヤーの表示させる入力方法
	int selectID_;		// プレイヤー選択・システム選択の保存
	int selectPlID_;	// 選択されているプレイヤー
	bool backToTheTitle_;	// タイトルに戻るフラグ
};