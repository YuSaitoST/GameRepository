#include "GameController.h"
#include "DontDestroyOnLoad.h"
#include <cassert>

GameController::GameController() {
	timer_ = new OriTimer(TIME_LIMIT[DontDestroy->GameMode_]);
}

GameController::~GameController() {
	delete timer_;
}

void GameController::Update(const float deltaTime) {
	timer_->Update(deltaTime);
}

bool GameController::GameFined() {
	if (DontDestroy->GameMode_ == DontDestroy->GAMEMODE::HAND_BALL)
		return timer_->TimeOut();
	else if (DontDestroy->GameMode_ <= DontDestroy->GAMEMODE::DODGE_BALL_2ON2)
		return false;  // 最後の1チームになったら

	assert(!"不正なゲームモードです__in GameController::GameFined()");
	return false;
}