#include "StartState.h"
#include "_Classes/_GameController/GameController.h"
#include "DontDestroyOnLoad.h"

StartState::StartState() {
	startTime_	= TIME_COUNT;
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
	blackOut_->Update(SPEED_FADE * deltaTime);
	countDown_->Update(deltaTime, (TIME_COUNT - (startTime_ - timer_->NowTime())));
}

void StartState::Render() {
	blackOut_->Render();
	countDown_->Render((TIME_COUNT - std::max(0.0f, (startTime_ - timer_->NowTime()))));
}

bool StartState::ChangeDrawing(GameController* controller) {
	return controller->gamePlay_ = timer_->TimeOut();
}