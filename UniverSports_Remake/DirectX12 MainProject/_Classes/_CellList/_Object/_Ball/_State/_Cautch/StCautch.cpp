#include "StCautch.h"
#include "_Classes/_CellList/ObjectManager.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "DontDestroyOnLoad.h"

void StCautch::Initialize() {
	myState_ = B_STATE::CAUTCH;
}

void StCautch::Update(ObjBall* ball) {
	if (!ball->IsInPlayerHands()) {
		ball->SwitchState(B_STATE::SHOT);
		return;
	}
	else if (ball->IsBreaked()) {
		ball->FlagResets();
		ball->SetOwnerID(-1);
		ball->SwitchColor(ObjBall::COLOR_TYPE::DEFAULT_COLOR);
		ball->SwitchState(B_STATE::FLOATING);
		return;
	}

	position_ = ObjectManager::PlayerHandsPos(ball->GetOwnerID());
	ball->PhysicsControll(Vector3(position_.x, position_.y, Z_MIN));
}