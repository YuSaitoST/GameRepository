#include "CharaSelect.h"
#include "LobbyScene.h"
#include "DontDestroyOnLoad.h"

CharaSelect::CharaSelect() {
	choices_		= new Choices(4);
	ui_arrows_		= new SelectArrows();
	se_decision_	= new SoundPlayer();
	se_cancel_		= new SoundPlayer();
	se_warning_		= new SoundPlayer();
	isDecision_		= false;
	isCansel_		= false;
}

CharaSelect::~CharaSelect() {
	delete se_warning_;
	delete se_cancel_;
	delete se_decision_;
	delete ui_arrows_;
	delete choices_;
}

void CharaSelect::Initialize(int index) {
	ui_arrows_->Initialize(ARROW_R_X[index], ARROW_L_X[index], ARROW_Y);
	se_decision_->Initialize(L"_Sounds\\_SE\\se_decision.wav", SOUND_TYPE::SE);
	se_cancel_->Initialize(L"_Sounds\\_SE\\_Lobby\\se_cancel.wav", SOUND_TYPE::SE);
	se_warning_->Initialize(L"_Sounds\\_SE\\_Lobby\\se_warning.wav", SOUND_TYPE::SE);
}

void CharaSelect::LoadAssets(DX9::SPRITE right, DX9::SPRITE left) {
	ui_arrows_->LoadAssets(right, left);
}

void CharaSelect::Update(const float deltaTime, const int index) {
	// 決定済みの時
	if (isDecision_) {
		// キャンセル処理
		if (Press.CancelKey(index)) {
			isDecision_ = false;
			se_cancel_->PlayOneShot();
		}
		return;
	}

	choices_->Update(Press.LeftKey(index), Press.RightKey(index));
	choices_->NextSelectOn(ui_arrows_->Update(index));

	isDecision_ = Press.DecisionKey(index);

	// 選択している色を代入
	DontDestroy->ChoseColor_[index] = choices_->SelectNum();

	// 決定したら、色とキャラの操作タイプを設定
	if (isDecision_) {
		// 色が重複していたら決定できない
		if (haveSameValue(index)) {
			isDecision_ = false;
			se_warning_->PlayOneShot();
			return;
		}

		LobbyScene::ChangeModel(index, DontDestroy->ChoseColor_[index]);
		DontDestroy->charaType_[index] = DontDestroy->CHARATYPE::PLAYER;
		se_decision_->PlayOneShot();
	}
	else if ((index != 0) && Press.TabKey()) {
		SelectToAvoidDupLicates(index);
		LobbyScene::ChangeModel(index, DontDestroy->ChoseColor_[index]);
		LobbyScene::ChangeStrategy(index);
		DontDestroy->charaType_[index] = DontDestroy->CHARATYPE::COM;
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

void CharaSelect::SelectToAvoidDupLicates(int index) {
	while (haveSameValue(index)) {
		DontDestroy->ChoseColor_[index] += 1;
		ValueLoop(DontDestroy->ChoseColor_[index], 0, 4 - 1);
	}
}

bool CharaSelect::haveSameValue(int index) {
	for (int _i = 0; _i < 4; ++_i) {
		// 自分のIDだったら調べなおす
		if (_i == index)
			continue;

		// 重複しているものがあればtrueを返す
		if (DontDestroy->ChoseColor_[index] == DontDestroy->ChoseColor_[_i])
			return true;
	}

	return false;
}

void CharaSelect::ValueLoop(int& num, int min, int max) {
	if (num < min)
		num = max;

	if (max < num)
		num = min;
}