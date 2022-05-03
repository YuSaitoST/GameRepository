#include "CharaSelect.h"
#include "LobbyScene.h"
#include "DontDestroyOnLoad.h"

CharaSelect::CharaSelect() {
	choices_ = new Choices(4);
	ui_arrows_ = new SelectArrows();
	se_decision_ = new SoundPlayer();
	se_cancel_ = new SoundPlayer();
	isDecision_ = false;
	//isTabsDecision_ = false;
	isCansel_ = false;
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
}

void CharaSelect::LoadAssets(DX9::SPRITE right, DX9::SPRITE left) {
	ui_arrows_->LoadAssets(right, left);
}

void CharaSelect::Update(const float deltaTime, const int index) {
	const bool inpDec = Press.PDecisionKey(0);  // b
	const bool inpCan = Press.PCancelKey(0);  // a

	if (DXTK->GamePadEvent[0].a) {
		bool inp = inpCan;
	}


	// 決定済みの時
	if (isDecision_) {
		//if (!isTabsDecision_)  // 多分いらない
			//isCansel_ = Press.CancelKey(index);

		// キャンセル処理
		if (Press.PCancelKey(index)) {
			isDecision_ = false;
			se_cancel_->PlayOneShot();
		}

		// キーボード操作によるキャンセル
		if (index == 0) {
			if (Press.KCancelKey()) {
				isDecision_ = false;
				se_cancel_->PlayOneShot();
			}
		}
		return;
	}

	choices_->Update(Press.LeftKey(index), Press.RightKey(index));
	choices_->NextSelectOn(ui_arrows_->Update(index));

	isDecision_ = Press.PDecisionKey(index);

	// キーボード操作による決定
	if (index == 0)
		isDecision_ = Press.KDecisionKey() || Press.PDecisionKey(index);


	// 選択している色を代入
	//if (index == 0)
		DontDestroy->ChoseColor_[index] = choices_->SelectNum();
	//else
	//	DontDestroy->ChoseColor_[index] = 1;

	// 決定したら、色とキャラの操作タイプを設定
	if (isDecision_) {
		LobbyScene::ChangeModel(index, DontDestroy->ChoseColor_[index]);
		DontDestroy->charaType_[index] = DontDestroy->CHARATYPE::PLAYER;
		se_decision_->PlayOneShot();
	}
	else if (Press.TabKey()) {
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