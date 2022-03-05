#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_StateOpe/StateOpeBase.h"
#include "_StateOpe/_Open/OpeClose.h"
#include "_StateOpe/_Close/OpeOpen.h"

using namespace DirectX;

class OperateUI {
public:
	OperateUI();
	virtual ~OperateUI() = default;

	void Initialize();
	void LoadAsset();
	void Update(const float deltaTime);
	void Render() const;

	void isPut();
	int isState() const { return num_state_; };
	bool isDisplayed() const { return isDisplay_; };

private:
	void AnimateOn() { state_ = &st_open_; };
	void AnimateOff() { state_ = &st_close_; };

private:
	OP_StateBase*	state_;
	OpeOpen			st_open_;
	OpeClose		st_close_;

	DX9::SPRITE sp_keybord_;
	DX9::SPRITE sp_gamepad_;

	SimpleMath::Vector3 pos_key_;
	SimpleMath::Vector3 pos_pad_;

	int num_state_;
	bool isDisplay_;
};