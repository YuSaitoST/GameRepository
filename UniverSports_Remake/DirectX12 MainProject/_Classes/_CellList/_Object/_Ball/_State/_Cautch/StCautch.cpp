#include "StCautch.h"
#include "_Classes/_CellList/ObjectManager.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "DontDestroyOnLoad.h"

void StCautch::Update(ObjBall* ball) {
	position_ = ObjectManager::PlayerHandsPos(ball->GetOwnerID());
	ball->PhysicsControll(Vector3(position_.x, position_.y, Z_MIN));

	if (!ball->IsInPlayerHands()) {
		ball->SwitchState(ball->STATE::SHOT);
	}
}