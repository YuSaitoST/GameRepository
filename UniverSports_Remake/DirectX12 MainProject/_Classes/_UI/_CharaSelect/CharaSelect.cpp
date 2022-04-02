#include "CharaSelect.h"
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

void CharaSelect::Initialize() {
	ui_arrows_->Initialize(283.0f, 100.0f, ARROW_Y);
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
	DontDestroy->ChoseColor_[index] = choices_->SelectNum();
}

void CharaSelect::Render(DX9::SPRITE& icon, DX9::SPRITE& decisions, DX9::SPRITE entry, SimpleMath::Vector3 adjustment) {
	ui_arrows_->Render(255, adjustment);
	DX9::SpriteBatch->DrawSimple(icon.Get(), SimpleMath::Vector3(103.0f,PICON_Y,0.0f) + adjustment);
	DX9::SpriteBatch->DrawSimple(decisions.Get(), SimpleMath::Vector3(140.0f, INPUT_Y, -100) + adjustment);

	if (isDecision_)
		DX9::SpriteBatch->DrawSimple(entry.Get(), SimpleMath::Vector3(108.0f, ENTRY_Y, -90) + adjustment);
}