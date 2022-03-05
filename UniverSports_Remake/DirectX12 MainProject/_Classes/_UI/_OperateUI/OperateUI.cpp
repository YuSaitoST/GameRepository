#include "OperateUI.h"

OperateUI::OperateUI() {
	state_		= &st_close_;
	sp_gamepad_ = nullptr;
	sp_keybord_	= nullptr;
	pos_key_	= SimpleMath::Vector3::Zero;
	num_state_	= 0;
	isDisplay_	= false;
}

void OperateUI::Initialize() {
	st_open_.Initialize();
	st_close_.Initialize();

	pos_pad_	= SimpleMath::Vector3(-1280.0f, 0.0f, -98.0f);
	pos_key_	= SimpleMath::Vector3(-1280.0f, 0.0f, -99.0f);
}

void OperateUI::LoadAsset() {
	sp_gamepad_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Title\\_Operate\\operate_gamepad.png");
	sp_keybord_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Title\\_Operate\\operate_keybord.png");
}

void OperateUI::Update(const float deltaTime) {
	pos_pad_	= state_->myPosPad();
	pos_key_	= state_->myPosKey();
	state_->Update(deltaTime, this);
}

void OperateUI::Render() const {
	DX9::SpriteBatch->DrawSimple(
		sp_gamepad_.Get(),
		pos_pad_
	);
	DX9::SpriteBatch->DrawSimple(
		sp_keybord_.Get(),
		pos_key_
	);
}

void OperateUI::isPut() {
	num_state_ = (num_state_ < 2)	? num_state_ + 1	: 0;
	num_state_ = ((num_state_ == 2) && (state_->myPosPad().x != 0.0f)) ? 0 : num_state_;
	isDisplay_ = (1 <= num_state_)	? true				: false;
	isDisplay_ ?
		AnimateOn() :
		AnimateOff();
	state_->SetPosPad(pos_pad_);
	state_->SetPosKey(pos_key_);
}