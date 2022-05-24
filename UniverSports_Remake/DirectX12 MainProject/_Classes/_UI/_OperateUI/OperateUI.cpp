#include "OperateUI.h"
#include "_Classes/_FileNames/FileNames.h"

OperateUI::OperateUI() : sp_gamepad_(DX9::SPRITE()), pos_pad_(DirectX::XMFLOAT3()) {
	state_		= &st_close_;
	num_state_	= 0;
	isDisplay_	= false;
}

void OperateUI::Initialize() {
	st_open_.Initialize();
	st_close_.Initialize();

	pos_pad_	= DirectX::XMFLOAT3(-1280.0f, 0.0f, -98.0f);
}

void OperateUI::LoadAsset() {
	sp_gamepad_ = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::GAMEPAD.c_str());
}

void OperateUI::Update(const float deltaTime) {
	pos_pad_	= state_->myPosPad();
	state_->Update(deltaTime, this);
}

void OperateUI::Render() const {
	DX9::SpriteBatch->DrawSimple(sp_gamepad_.Get(), pos_pad_);
}

/**
* @brief 入力された際にアニメーションを切り替える処理
*/
void OperateUI::isPut() {
	num_state_ = (num_state_ < OPERATE_COUNT)	? num_state_ + 1	: 0;
	isDisplay_ = (num_state_ == OPERATE_COUNT);
	num_state_ = (isDisplay_ && (state_->myPosPad().x != 0.0f)) ? 0 : num_state_;
	isDisplay_ ? AnimateOn() : AnimateOff();
	state_->SetPosPad(pos_pad_);
}