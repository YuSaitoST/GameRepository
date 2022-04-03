#include "GameController.h"
#include "DontDestroyOnLoad.h"
#include <cassert>

GameController::GameController() {
	startTime_	= TIME_LIMIT[DontDestroy->GameMode_] + TIME_COUNT;
	timer_		= new OriTimer(startTime_);
	countDown_	= new CountDownUI();
}

GameController::~GameController() {
	delete countDown_;
	delete timer_;
}

void GameController::Initialize() {
	countDown_->Initialize();
}

void GameController::LoadAssets() {
	countDown_->LoadAssets();
}

void GameController::Update(const float deltaTime) {
	timer_->Update(deltaTime);
	countDown_->Update(deltaTime, (TIME_COUNT - std::max(0.0f, (startTime_ - timer_->NowTime()))));
}

void GameController::Render() {
	if (timer_->NowTime() < TIME_LIMIT[DontDestroy->GameMode_])
		return;

	countDown_->Render((TIME_COUNT - std::max(0.0f, (startTime_ - timer_->NowTime()))));
}

bool GameController::GameFined() {
	if (DontDestroy->GameMode_ == DontDestroy->GAMEMODE::HAND_BALL)
		return timer_->TimeOut();
	else if (DontDestroy->GameMode_ <= DontDestroy->GAMEMODE::DODGE_BALL_2ON2)
		return false;  // 最後の1チームになったら

	assert(!"不正なゲームモードです__in GameController::GameFined()");
	return false;
}