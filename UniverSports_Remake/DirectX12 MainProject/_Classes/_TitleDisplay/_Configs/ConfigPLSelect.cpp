#include "ConfigPLSelect.h"
#include "_Classes/_InputManager/UseKeyChecker.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/UIPosition.h"
#include "_Classes/_TitleDisplay/ConfigDisplay.h"

void ConfigPLSelect::Initialize() {
	ui_cursor_->Initialize(CURSOR_POS_X, CURSOR_POS_Y, CURSOR_MOVE_Y);
}

void ConfigPLSelect::LoadAssets() {
	ui_cursor_->LoadAsset(USFN_SP::ARROW_R.c_str());
}

void ConfigPLSelect::Update(const float deltaTime, ConfigDisplay* conDisplay) {
	ui_cursor_->Update(4, INPSystem.UpKey(0), INPSystem.DownKey(0));

	if (INPSystem.DecisionKey(0)) {
		conDisplay->SE_PlayDecision();
		conDisplay->SelectPlayer(ui_cursor_->SelectNum());
		conDisplay->ChangeSelect((int)ConfigSelector::InpSystem);
	}
	else if (INPSystem.CancelKey(0)) {
		conDisplay->SE_PlayCancel();
		conDisplay->BackToTheTitle();
	}
}

void ConfigPLSelect::Render(DX9::SPRITEFONT font) {
	ui_cursor_->Render(255);

	MessageRender(font, (int)ConfigSelector::Player);
}