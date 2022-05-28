#include "StCautch.h"
#include "_Classes/_CellList/ObjectManager.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_CellList/_Object/_Ball/_State/_Shot/StShot.h"
#include "_Classes/_CellList/_Object/_Ball/_State/_Float/StFloat.h"
#include "DontDestroyOnLoad.h"

void StCautch::Initialize() {
	myState_ = B_STATE::CAUTCH;
}

void StCautch::Update(ObjBall* ball) {
	if (!ball->IsInPlayerHands()) {
		StShot* shot = new StShot();
		ball->SwitchState(shot);
		return;
	}
	else if (ball->IsBreaked()) {
		ball->FlagResets();
		ball->SetOwnerID(-1);
		StFloat* flo = new StFloat();
		ball->SwitchState(flo);
		ball->SwitchColor(ObjBall::COLOR_TYPE::DEFAULT_COLOR);
		return;
	}

	position_ = ObjectManager::PlayerHandsPos(ball->GetOwnerID());
	ball->PhysicsControll(Vector3(position_.x, position_.y, Z_MIN));
}