#include "FinishState.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

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
	blackOut_->Update(GAMES_PARAM.FN_FADEIN * deltaTime);
}

void FinishState::Render() {
	ui_finish_->Render();
	blackOut_->Render();
}

bool FinishState::ChangeDrawing(GameController* controller) {
	const bool _blackOutFine	= blackOut_->isDone();
	const bool _finishUIFine	= ui_finish_->isAnimationFine();
	const bool _seFine			= se_whistle_->PlayOneShot(0.016f);
	return _blackOutFine && _finishUIFine && _seFine;
	//return blackOut_->isDone() && ui_finish_->isAnimationFine() && se_whistle_->PlayOneShot(0.016f);
}