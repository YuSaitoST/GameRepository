#include "CharaSelect.h"
#include "LobbyScene.h"
#include "DontDestroyOnLoad.h"

CharaSelect::CharaSelect() {
	choices_ = new Choices(4);
	ui_arrows_ = new SelectArrows();
	isDecision_ = false;
}

CharaSelect::~CharaSelect() {
	delete ui_arrows_;
	delete choices_;
}

void CharaSelect::Initialize(int index) {
	ui_arrows_->Initialize(ARROW_R_X[index], ARROW_L_X[index], ARROW_Y);
}

void CharaSelect::LoadAssets(DX9::SPRITE right, DX9::SPRITE left) {
	ui_arrows_->LoadAssets(right, left);
}

void CharaSelect::Update(const float deltaTime, const int index) {
	if (isDecision_) {
		isDecision_ = !Press.CancelKey();
		return;
	}

	choices_->Update(Press.LeftKey(), Press.RightKey());
	ui_arrows_->Update();

	isDecision_ = Press.DecisionKey();
	if (isDecision_)
		LobbyScene::ChangeModel(index, choices_->SelectNum());

	DontDestroy->ChoseColor_[index] = choices_->SelectNum();
}

void CharaSelect::Render(DX9::SPRITE& icon, DX9::SPRITE& decisions, DX9::SPRITE entry, int index) {
	ui_arrows_->Render(255);
	DX9::SpriteBatch->DrawSimple(icon.Get(), SimpleMath::Vector3(PICON_X[index], PICON_Y, 0.0f));
	DX9::SpriteBatch->DrawSimple(decisions.Get(), SimpleMath::Vector3(INPUT_X[index], INPUT_Y, -100));

	if (isDecision_)
		DX9::SpriteBatch->DrawSimple(entry.Get(), SimpleMath::Vector3(ENTRY_X[index], ENTRY_Y, -90));
}