#include "NormalDisplay.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_UI/_Fade/Fade.h"

NormalDisplay::NormalDisplay() : ui_alpha_(0.0f), isOtherSelect_(0) {
	se_decision_	= std::make_unique<SoundPlayer>();
	time_start_		= std::make_unique<CountTimer>(GAMES_PARAM.TL_TIME_LOGO_DISPLAY);
	time_demo_		= std::make_unique<CountTimer>(GAMES_PARAM.TL_DEMO_PLAYBACK);
	cursor_			= std::make_unique<Cursor>();
	mode_choices_	= std::make_unique<Choices>();
	ui_arrows_		= std::make_unique<SelectArrows>();
	operate_		= std::make_unique<OperateUI>();
	blackOut_		= std::make_unique<BlackOut>();
	movie_			= std::make_unique<MoviePlayer>();

	ui_text_[0]		= std::make_unique<ChoicesText>();
	ui_text_[1]		= std::make_unique<ChoicesText>();

	selectID_[0] = selectID_[1] = 0;
	pos_y_arrows_[0] = pos_y_arrows_[1] = 0;
}

void NormalDisplay::Initialize() {
	auto _texPos = US2D::Pos::Get().TitleParam();

	se_decision_->Initialize(USFN_SOUND::SE::DECISION_TITLE, SOUND_TYPE::SE, 2.0f);
	mode_choices_->Initialize();
	cursor_->Initialize(CURSOR_POS_X, CURSOR_POS_Y, 0);
	ui_arrows_->Initialize(_texPos.RightArrowX, _texPos.LeftArrowX);
	operate_->Initialize();
	blackOut_->Initialize(BLACKOUT_MODE::FADE_OUT);
	
	ui_text_[0]->Initialize(DirectX::XMFLOAT3(_texPos.TextX, _texPos.TextY[0], (int)US2D::Layer::TITLE::UI_TEXT));
	ui_text_[1]->Initialize(DirectX::XMFLOAT3(_texPos.TextX, _texPos.TextY[1], (int)US2D::Layer::TITLE::UI_TEXT));

	pos_y_arrows_[0] = _texPos.ArrowY;
	pos_y_arrows_[1] = _texPos.TextY[1];
}

void NormalDisplay::LoadAssets() {
	movie_->LoadAsset(USFN_MV::TITLE_BG);
	cursor_->LoadAsset(USFN_SP::CURSOR);
	ui_arrows_->LoadAssets();
	operate_->LoadAsset();
	blackOut_->LoadAsset();

	ui_text_[0]->LoadAsset(COUNT_MAX[0], USFN_SP::UI_TEXT_MODE[0], USFN_SP::UI_TEXT_MODE[1], USFN_SP::UI_TEXT_MODE[2]);
	ui_text_[1]->LoadAsset(COUNT_MAX[1], USFN_SP::UI_TEXT_OTHER[0], USFN_SP::UI_TEXT_OTHER[1]);
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

	// カーソルが移動したら
	if (cursor_->Update(CHOICES, INPSystem.DownKeyboard(), INPSystem.UpKeyboard())) {
		mode_choices_->SetSelectNum(selectID_[cursor_->SelectNum()]);
	}

	time_demo_->Update(deltaTime);

	// 何かしらのボタンが押されていたらタイマーをリセットする
	if (INPSystem.AnyKey())
		time_demo_->Reset();

	mode_choices_->Update(COUNT_MAX[cursor_->SelectNum()], INPSystem.LeftKeyboard(), INPSystem.RightKeyboard());
	mode_choices_->NextSelectOn(ui_arrows_->Update(0));

	selectID_[cursor_->SelectNum()] = std::min(std::max(mode_choices_->SelectNum(), 0), COUNT_MAX[cursor_->SelectNum()] - 1);

	// 選択肢UIの表示サイズの更新
	for (int _t = 0; _t < CHOICES; ++_t) {
		(_t == cursor_->SelectNum()) ?
			ui_text_[_t]->GetBigger(deltaTime) :
			ui_text_[_t]->GetSmaller(deltaTime);
	}

	// 決定ボタンを押したら、選択した項目に合わせた処理を行う
	if (INPSystem.DecisionKeyboard()) {
		se_decision_->PlayOneShot();
		
		const int _mode_selects = mode_choices_->SelectNum();

		if (cursor_->SelectNum() == 1) {
			isOtherSelect_ = _mode_selects + 1;

			if (_mode_selects == 0) {
				operate_->isPut();
			}
		}
		else if (!operate_->isDisplayed()) {
			blackOut_->ChangeMode(BLACKOUT_MODE::FADE_IN);
			DontDestroy->GameMode_.SelectMode((GAMEMODE)_mode_selects);
		}
	}

	operate_->Update(deltaTime);

	return NextScene::Continue;
}

void NormalDisplay::Render() {
	movie_->Render(DirectX::XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::TITLE::BG_BACK));
	ui_arrows_->Render(ui_alpha_, pos_y_arrows_[cursor_->SelectNum()]);
	operate_->Render();
	blackOut_->Render();

	ui_text_[0]->Render(ui_alpha_, selectID_[0]);
	ui_text_[1]->Render(ui_alpha_, selectID_[1]);
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
DISPLAYMODE NormalDisplay::IsChange() {
	if (isOtherSelect_ == 2) {
		isOtherSelect_ = 0;
		return DISPLAYMODE::DISPLAY_CONFIG;
	}
	else if (time_demo_->TimeOut()) {
		return DISPLAYMODE::DISPLAY_DEMO;
	}

	return DISPLAYMODE::DISPLAY_NONE;
}

void NormalDisplay::ReDisplayInitialize() {
	cursor_->SetSelectNum(0);
	movie_->Play();
}