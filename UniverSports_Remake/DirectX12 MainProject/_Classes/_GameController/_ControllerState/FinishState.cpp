#include "FinishState.h"
#include "_Classes/_FileNames/FileNames.h"

FinishState::FinishState() {
	ui_finish_	= std::make_unique<Finish>();
	blackOut_	= std::make_unique<BlackOut>();
	se_whistle_ = std::make_unique<SoundPlayer>();
}

void FinishState::Initialize() {
	ui_finish_->Initialize();
	blackOut_->Initialize(BLACKOUT_MODE::FADE_IN);
	se_whistle_->Initialize(USFN_SOUND::SE::WHISTLE, SOUND_TYPE::SE, 1.0f);
}

void FinishState::LoadAsstes() {
	ui_finish_->LoadAssets();
	blackOut_->LoadAsset();
}

void FinishState::Update(const float deltaTime) {
	ui_finish_->Update(deltaTime);
	blackOut_->Update(SPEED_FADE * deltaTime);
}

void FinishState::Render() {
	ui_finish_->Render();
	blackOut_->Render();
}

bool FinishState::ChangeDrawing(GameController* controller) {
	return blackOut_->isDone() && ui_finish_->isAnimationFine() && se_whistle_->PlayOneShot(0.016f);
}