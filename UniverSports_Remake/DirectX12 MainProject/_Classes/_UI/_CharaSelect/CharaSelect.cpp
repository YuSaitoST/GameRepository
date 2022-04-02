#include "CharaSelect.h"

CharaSelect::CharaSelect() {
	choices_ = new Choices(4);
	ui_arrows_ = new SelectArrows();
}

CharaSelect::~CharaSelect() {
	delete ui_arrows_;
	delete choices_;
}

void CharaSelect::Initialize() {
	ui_arrows_->Initialize(283.0f, 100.0f, 600.0f);
}

void CharaSelect::LoadAssets(DX9::SPRITE right, DX9::SPRITE left) {
	ui_arrows_->LoadAssets(right, left);
}

void CharaSelect::Update(const float deltaTime, const int index) {
	choices_->Update(Press.LeftKey(), Press.RightKey());
	Choose();
	ui_arrows_->Update();
}

void CharaSelect::Render() {
	ui_arrows_->Render(255);
}

void CharaSelect::Choose() {
	const bool _inRight = Press.RightKey();
	const bool _inLeft = Press.LeftKey();

	INPUT_SELECT _input = _inRight ? AL_RIGHT : _inLeft ? AL_LEFT : ui_arrows_->NowState();
	ui_arrows_->SetAnimation(_input);
}