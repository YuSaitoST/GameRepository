#include "StartState.h"
#include "_Classes/_GameController/GameController.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "DontDestroyOnLoad.h"

StartState::StartState() {
	startTime_	= GAMES_PARAM.MN_COUNTDOWN;
	timer_		= std::make_unique<CountTimer>(startTime_);
	countDown_	= std::make_unique<CountDownUI>();
	blackOut_	= std::make_unique<BlackOut>();
}

void StartState::Initialize() {
	countDown_->Initialize();
	blackOut_->Initialize(BLACKOUT_MODE::FADE_OUT);
}

void StartState::LoadAsstes() {
	countDown_->LoadAssets();
	blackOut_->LoadAsset();
}

void StartState::Update(const float deltaTime) {
	timer_->Update(deltaTime);
	blackOut_->Update(GAMES_PARAM.MN_FADEOUT * deltaTime);
	countDown_->Update(deltaTime, (GAMES_PARAM.MN_COUNTDOWN - (startTime_ - timer_->NowTime())));
}

void StartState::Render() {
	blackOut_->Render();
	countDown_->Render((GAMES_PARAM.MN_COUNTDOWN - std::max(0.0f, (startTime_ - timer_->NowTime()))));
}

bool StartState::ChangeDrawing(GameController* controller) {
	return controller->gamePlay_ = timer_->TimeOut();
}