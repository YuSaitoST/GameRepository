#include "ConfigDisplay.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_UI/_Fade/Fade.h"

#include "_Configs/ConfigPLSelect.h"
#include "_Configs/ConfigSySelect.h"

ConfigDisplay::ConfigDisplay() : selectID_(0), selectPlID_(0) {
	configSelector_.push_back(std::make_unique<ConfigPLSelect>());
	configSelector_.push_back(std::make_unique<ConfigSySelect>());

	se_decision_	= std::make_unique<SoundPlayer>();
	se_cancel_		= std::make_unique<SoundPlayer>();
}

void ConfigDisplay::Initialize() {
	for (int i = 0; i < 2; ++i) {
		configSelector_[i]->Initialize();
	}

	std::vector<InputSystem> defaultSystem = INPSystem.GetNowInputSystem();
	for (int i = 0; i < PlayerCount; ++i) {
		selectSystemID_[i] = defaultSystem[i];
	}

	se_decision_->Initialize(USFN_SOUND::SE::DECISION_TITLE, SOUND_TYPE::SE, 2.0f);
	se_cancel_->Initialize(USFN_SOUND::SE::CANCEL, SOUND_TYPE::SE, 0.0f);;
}

void ConfigDisplay::LoadAssets() {
	font_selects_	= DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 35);
	font_message_	= DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 20);
	sp_bg_			= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::CONFIG_BG.c_str());

	for (int i = 0; i < 2; ++i) {
		configSelector_[i]->LoadAssets();
	}
}

NextScene ConfigDisplay::Update(const float deltaTime) {
	configSelector_[selectID_]->Update(deltaTime, this);

	return NextScene::Continue;
}

void ConfigDisplay::Render() {
	DX9::SpriteBatch->DrawSimple(sp_bg_.Get(), DirectX::XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::TITLE::BG_BACK));

	std::wstring ipAddr = L"IPアドレス : ";
	ipAddr += INPSystem.GetIPAddress().c_str();

	DX9::SpriteBatch->DrawString(
		font_message_.Get(),
		DirectX::XMFLOAT2(IP_POS_X, IP_POS_Y),
		DX9::Colors::Black,
		ipAddr.c_str()
	);

	for (int i = 0; i < PlayerCount; ++i) {
		DX9::SpriteBatch->DrawString(
			font_selects_.Get(),
			DirectX::XMFLOAT2(POS_PlayerID_X, POS_AllTexts_Y[i]),
			DX9::Colors::Black,
			TXT_PlayerID_[i].c_str()
		);

		DX9::SpriteBatch->DrawString(
			font_selects_.Get(),
			DirectX::XMFLOAT2(POS_Operates_X, POS_AllTexts_Y[i]),
			DX9::Colors::Black,
			TXT_Operates_[(int)selectSystemID_[i]].c_str()
		);
	}

	configSelector_[selectID_]->Render(font_message_);
}

/**
 * @brief 画面表示を切り替えるかの判定
 * @return デモプレイ再生までの時間が経過したらtrue
*/
DISPLAYMODE ConfigDisplay::IsChange() {
	if (backToTheTitle_) {
		INPSystem.AllInputSystemSetter();
		return DISPLAYMODE::DISPLAY_NORMAL;
	}

	return DISPLAYMODE::DISPLAY_NONE;
}

void ConfigDisplay::ReDisplayInitialize() {
	selectID_		= 0;
	selectPlID_		= 0;
	backToTheTitle_ = false;
}



void ConfigDisplay::DecisionInpSystem() {
	INPSystem.SetInputSystem(selectSystemID_[selectPlID_], selectPlID_);

	const std::vector<InputSystem> _inpSystem = INPSystem.GetNowInputSystem();
	for (int i = 0; i < PlayerCount; ++i) {
		selectSystemID_[i] = _inpSystem[i];
	}
}

void ConfigDisplay::CancelSystemSelect() {
	std::vector<InputSystem> defaultSystem = INPSystem.GetNowInputSystem();
	for (int i = 0; i < 4; ++i) {
		selectSystemID_[i] = defaultSystem[i];
	}
}