#include "ConfigSySelect.h"
#include "_Classes/_InputManager/UseKeyChecker.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_TitleDisplay/ConfigDisplay.h"

ConfigSySelect::ConfigSySelect() : arrow_pos_y_(CURSOR_MOVE_Y) {
	ui_arrows_		= std::make_unique<SelectArrows>();
	systemChoices_	= std::make_unique<Choices>();

}

void ConfigSySelect::Initialize() {
	ui_arrows_->Initialize(CURSOR_RIGHT_X, CURSOR_LEFT_X);
	systemChoices_->Initialize();
}

void ConfigSySelect::LoadAssets() {
	ui_arrows_->LoadAssets();
}

void ConfigSySelect::Update(const float deltaTime, ConfigDisplay* conDisplay) {
	systemChoices_->Update(4, INPSystem.LeftKey(0), INPSystem.RightKey(0));
	systemChoices_->NextSelectOn(ui_arrows_->Update(0));

	arrow_pos_y_ = 160.0f + 85 * conDisplay->GetSelectPlayer();

	conDisplay->UpdateSelectSystem(systemChoices_->SelectNum());

	if (INPSystem.DecisionKey(0)) {
		systemChoices_->SetSelectNum(0);
		conDisplay->SE_PlayDecision();
		conDisplay->DecisionInpSystem();
		conDisplay->ChangeSelect((int)ConfigSelector::Player);
	}
	else if (INPSystem.CancelKey(0)) {
		systemChoices_->SetSelectNum(0);
		conDisplay->SE_PlayCancel();
		conDisplay->CancelSystemSelect();
		conDisplay->ChangeSelect((int)ConfigSelector::Player);
	}
}

void ConfigSySelect::Render(DX9::SPRITEFONT font) {
	ui_arrows_->Render(255, arrow_pos_y_);

	MessageRender(font, (int)ConfigSelector::InpSystem);
}