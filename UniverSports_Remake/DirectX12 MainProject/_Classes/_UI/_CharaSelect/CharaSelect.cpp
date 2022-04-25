#include "CharaSelect.h"
#include "LobbyScene.h"
#include "DontDestroyOnLoad.h"

CharaSelect::CharaSelect() {
	choices_ = new Choices(4);
	ui_arrows_ = new SelectArrows();
	se_decision_ = new SoundPlayer();
	se_cancel_ = new SoundPlayer();
	isDecision_ = false;
	isTabsDecision_ = false;
}

CharaSelect::~CharaSelect() {
	delete se_cancel_;
	delete se_decision_;
	delete ui_arrows_;
	delete choices_;
}

void CharaSelect::Initialize(int index) {
	ui_arrows_->Initialize(ARROW_R_X[index], ARROW_L_X[index], ARROW_Y);
	se_decision_->Initialize(L"_Sounds\\_SE\\se_decision.wav", SOUND_TYPE::SE, 2);
	se_cancel_->Initialize(L"_Sounds\\_SE\\_Lobby\\se_cancel.wav", SOUND_TYPE::SE, 2);

	if (index != 0)
		DontDestroy->ChoseColor_[index] = 1;
}

void CharaSelect::LoadAssets(DX9::SPRITE right, DX9::SPRITE left) {
	ui_arrows_->LoadAssets(right, left);
}

void CharaSelect::Update(const float deltaTime, const int index) {
	if (isDecision_) {
		if (!isTabsDecision_)
			isDecision_ = !Press.CancelKey();

		if (!isDecision_)
			se_cancel_->PlayOneShot();
		return;
	}

	if (index == 0) {
		choices_->Update(Press.LeftKey(), Press.RightKey());
		ui_arrows_->Update();

		isDecision_ = Press.DecisionKey();
	}
	else {
		isTabsDecision_ = Press.TabKey();
	}

	if (index == 0)
		DontDestroy->ChoseColor_[index] = choices_->SelectNum();
	else
		DontDestroy->ChoseColor_[index] = 1;

	if (isDecision_) {
		LobbyScene::ChangeModel(index, DontDestroy->ChoseColor_[index]);
		
		se_decision_->PlayOneShot();
	}
	else if (isTabsDecision_) {
		LobbyScene::ChangeModel(index, DontDestroy->ChoseColor_[index]);
		LobbyScene::ChangeStrategy(index);

		se_decision_->PlayOneShot();
		isDecision_ = true;
	}
}

void CharaSelect::Render(DX9::SPRITE& icon, DX9::SPRITE& decisions, DX9::SPRITE entry, int index) {
	ui_arrows_->Render(255);
	DX9::SpriteBatch->DrawSimple(icon.Get(), SimpleMath::Vector3(PICON_X[index], PICON_Y, 0.0f));
	DX9::SpriteBatch->DrawSimple(decisions.Get(), SimpleMath::Vector3(INPUT_X[index], INPUT_Y, -100));

	if (isDecision_)
		DX9::SpriteBatch->DrawSimple(entry.Get(), SimpleMath::Vector3(ENTRY_X[index], ENTRY_Y, -90));
}