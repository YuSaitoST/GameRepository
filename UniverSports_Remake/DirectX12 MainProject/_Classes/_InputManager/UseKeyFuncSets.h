/**
 * @file UseKeyFuncSets.h
 * @brief ゲームで用いる入力を管理するクラス
 * @author 齋藤優宇
 * @date 2021/09/09
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "InputDevice.h"

class UseKeyFuncSets {
public:
	UseKeyFuncSets() {}
	virtual ~UseKeyFuncSets() {}

	virtual void Accepts(const int index) = 0;
	virtual void SetInputFlag(VPInput::VPInpSet vpInput) = 0;

	virtual bool AnyKey() = 0;
	virtual bool UpKey(const int index) = 0;
	virtual bool DownKey(const int index) = 0;
	virtual bool LeftKey(const int index) = 0;
	virtual bool RightKey(const int index) = 0;
	virtual bool DecisionKey(const int index) = 0;
	virtual bool CancelKey(const int index) = 0;

	// どうするか考えておく
	//virtual bool MiniGameFinedKey(const int index) = 0;

	virtual bool ThrasherKey(const int index) = 0;
	virtual bool ShotKey(const int index) = 0;
	virtual DirectX::SimpleMath::Vector2 MoveDirection(const int index) = 0;

protected:
	std::unique_ptr<InputDevice> input_;
};


class NoneUseKey : public UseKeyFuncSets {
public:
	NoneUseKey() {}
	virtual ~NoneUseKey() {}

	virtual void Accepts(const int index) override {}
	virtual void SetInputFlag(VPInput::VPInpSet vpInput) override {}

	virtual bool AnyKey() override { return false; }
	virtual bool UpKey(const int index) override { return false; }
	virtual bool DownKey(const int index) override { return false; }
	virtual bool LeftKey(const int index) override { return false; }
	virtual bool RightKey(const int index) override { return false; }
	virtual bool DecisionKey(const int index) override { return false; }
	virtual bool CancelKey(const int index) override { return false; }

	//virtual bool MiniGameFinedKey(const int index) override { return false; }

	virtual bool ThrasherKey(const int index) override { return false; }
	virtual bool ShotKey(const int index) override { return false; }
	virtual DirectX::SimpleMath::Vector2 MoveDirection(const int index) override { return DirectX::SimpleMath::Vector2::Zero; }
};