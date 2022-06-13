#include "NormalDisplay.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_UI/_Fade/Fade.h"

NormalDisplay::NormalDisplay() : ui_alpha_(0.0f) {
	se_decision_	= std::make_unique<SoundPlayer>();
	time_start_		= std::make_unique<CountTimer>(GAMES_PARAM.TL_TIME_LOGO_DISPLAY);
	time_demo_		= std::make_unique<CountTimer>(GAMES_PARAM.TL_DEMO_PLAYBACK);
	cursor_			= std::make_unique<Cursor>();
	mode_choices_	= std::make_unique<Choices>();
	ui_arrows_		= std::make_unique<SelectArrows>();
	operate_		= std::make_unique<OperateUI>();
	blackOut_		= std::make_unique<BlackOut>();
	text_			= nullptr;
}

void NormalDisplay::Initialize() {
	se_decision_->Initialize(USFN_SOUND::SE::DECISION_TITLE, SOUND_TYPE::SE, 2.0f);

	mode_choices_->Initialize();
	cursor_->Initialize();
	ui_arrows_->Initialize(US2D::Pos::Get().TitleParam().RightArrowX, US2D::Pos::Get().TitleParam().LeftArrowX, US2D::Pos::Get().TitleParam().ArrowY);
	operate_->Initialize();
	blackOut_->Initialize(BLACKOUT_MODE::FADE_OUT);

	for (int _u = 0; _u < CHOICES; ++_u) {
		nowText_[_u][0].Initialize(_u, DirectX::XMFLOAT3(US2D::Pos::Get().TitleParam().TextX, US2D::Pos::Get().TitleParam().TextY[_u], (int)US2D::Layer::TITLE::UI_TEXT));
		nowText_[_u][1].Initialize(_u, DirectX::XMFLOAT3(US2D::Pos::Get().TitleParam().TextX, US2D::Pos::Get().TitleParam().TextY[_u], (int)US2D::Layer::TITLE::UI_TEXT));
		nowText_[_u][2].Initialize(_u, DirectX::XMFLOAT3(US2D::Pos::Get().TitleParam().TextX, US2D::Pos::Get().TitleParam().TextY[_u], (int)US2D::Layer::TITLE::UI_TEXT));
	}

	// 最初に選択状態にする選択肢を代入
	text_ = &nowText_[0][0];
}

void NormalDisplay::LoadAssets() {
	movie_->LoadAsset(USFN_MV::TITLE_BG);
	cursor_->LoadAsset(USFN_SP::CURSOR);
	ui_arrows_->LoadAssets();
	operate_->LoadAsset();
	blackOut_->LoadAsset();

	for (int _u = 0; _u < CHOICES; ++_u) {
		nowText_[_u][0].LoadAsset(USFN_SP::UI_TEXT[_u][0]);
		nowText_[_u][1].LoadAsset(USFN_SP::UI_TEXT[_u][1]);
		nowText_[_u][2].LoadAsset(USFN_SP::UI_TEXT[_u][2]);
	}
}

NextScene NormalDisplay::Update(const float deltaTime) {
	time_start_->Update(deltaTime);
	blackOut_->Update(SPEED_FADE[blackOut_->GetMode()] * deltaTime);

	// タイトルの表示に合わせてUIをフェードインさせる
	if (time_start_->NowTime() <= GAMES_PARAM.TL_UI_DISPLAY)
		FADE::In(ui_alpha_, FADE::COLORMAX, deltaTime * SPEED_ALPHA);

	// タイトルが表示されるまで操作不可
	if (!time_start_->TimeOut())
		return NextScene::Continue;

	// 決定音がなり終わったらキャラ選択画面へ
	if (!DontDestroy->GameMode_.isNotDecision()) {
		if (se_decision_->PlayOneShot(deltaTime) && blackOut_->isDone())
			return NextScene::LobbyScene;
		else
			return NextScene::Continue;
	}

	movie_->Update();
	cursor_->Update(CHOICES);
	time_demo_->Update(deltaTime);

	// 何かしらのボタンが押されていたらタイマーをリセットする
	if (Press.AnyKey())
		time_demo_->Reset();

	// モード選択
	if (cursor_->SelectNum() == 0) {
		mode_choices_->Update(MODE, Press.LeftKey(0), Press.RightKey(0));
		mode_choices_->NextSelectOn(ui_arrows_->Update(0));
	}

	text_ = &nowText_[cursor_->SelectNum()][mode_choices_->SelectNum()];

	// 選択肢UIの表示サイズの更新
	for (int _t = 0; _t < CHOICES; ++_t) {
		(_t == cursor_->SelectNum()) ?
			nowText_[_t][mode_choices_->SelectNum()].GetBigger(deltaTime) :
			nowText_[_t][mode_choices_->SelectNum()].GetSmaller(deltaTime);
	}

	/*
		決定ボタンを押したら、選択した項目に合わせた処理を行う
	*/
	if (Press.DecisionKey(0)) {
		se_decision_->PlayOneShot();

		if (cursor_->SelectNum() == 1)
			operate_->isPut();
		else if (!operate_->isDisplayed()) {
			blackOut_->ChangeMode(BLACKOUT_MODE::FADE_IN);
			DontDestroy->GameMode_.SelectMode((GAMEMODE)mode_choices_->SelectNum());
		}
	}

	operate_->Update(deltaTime);


	return NextScene::Continue;
}

void NormalDisplay::Render() {
	movie_->Render(DirectX::XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::TITLE::BG_MOVIE));
	ui_arrows_->Render(ui_alpha_);
	operate_->Render();
	blackOut_->Render();

	/*
		選択肢のテキストを初期化
		ループ回数を削減するために、選択肢の数が確定している上下の選択は並べて記述
	*/
	nowText_[0][mode_choices_->SelectNum()].Render(ui_alpha_);
	nowText_[1][mode_choices_->SelectNum()].Render(ui_alpha_);
}

/**
 * @brief 画面表示を切り替える際に表示状態をリセットする
*/
void NormalDisplay::Reset() {
	time_demo_->Reset();
}

/**
 * @brief 画面表示を切り替えるかの判定
 * @return デモプレイ再生までの時間が経過したらtrue
*/
bool NormalDisplay::IsChange() {
	return time_demo_->TimeOut();
}