#include "StStandby.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_GameController/GameController.h"

void StStandby::Initialize() {
	position_ = Vector2(99.0f, 99.0f);
}

void StStandby::Update(ObjBall* ball) {
	if (GameController::GamePlay())
		ball->SwitchState(ObjBall::STATE::FLOAT);
}