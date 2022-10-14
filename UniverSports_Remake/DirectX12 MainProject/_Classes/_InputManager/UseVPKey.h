/**
 * @file UseVPKey.h
 * @brief バーチャルパッドの入力管理クラス
 * @author 齋藤優宇
 * @date 2021/09/09
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "UseKeyFuncSets.h"
#include "YsVirtualPad.h"

class UseVPKey : public UseKeyFuncSets {
public:
	UseVPKey() { input_ = std::make_unique<YsVirtualPad>(); }
	virtual ~UseVPKey() {}

	virtual void Accepts(const int index) override { input_->accepts(index); }
	virtual void SetInputFlag(VPInput::VPInpSet vpInput) override { input_->set_inputflag(vpInput); }

	virtual bool AnyKey		()					override { return input_->get_anykey(); }
	virtual bool UpKey		(const int index)	override { return input_->get_key((int)GM_VPAD::P_UP); }
	virtual bool DownKey	(const int index)	override { return input_->get_key((int)GM_VPAD::P_DOWN); }
	virtual bool LeftKey	(const int index)	override { return input_->get_key((int)GM_VPAD::P_LEFT); }
	virtual bool RightKey	(const int index)	override { return input_->get_key((int)GM_VPAD::P_RIGHT); }
	virtual bool DecisionKey(const int index)	override { return input_->get_key((int)GM_VPAD::P_B); }
	virtual bool CancelKey	(const int index)	override { return input_->get_key((int)GM_VPAD::P_A); }

	// どうするか考えておく
	//virtual bool MiniGameFinedKey(const int index) override { return false; }

	virtual bool ThrasherKey(const int index) override { return input_->get_key((int)GM_VPAD::P_B); }
	virtual bool ShotKey(const int index) override { return input_->get_key((int)GM_VPAD::P_A); }
	virtual DirectX::SimpleMath::Vector2 MoveDirection(const int index) override { return input_->get_direction(index); }
};