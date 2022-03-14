#include "StCautch.h"
#include "_Classes/_CellList/ObjectManager.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "DontDestroyOnLoad.h"

void StCautch::Initialize() {
	
}

void StCautch::Update(ObjBall* ball) {
	position_ = ObjectManager::PlayerHandsPos(ball->GetOwnerID());
	ball->PhysicsControll(Vector3(position_.x, position_.y, Z_MIN));

	if (!ball->IsInPlayerHands())
		ball->SwitchState(ball->STATE::SHOT);

	//if (ball->IsHit()) {
	//	ball->SwitchState(ball->STATE::FLOAT);
	//	ball->SetMaterial();

	//	return;
	//}

	//if (ball->IsShot()) {
	//	ball->SwitchState(ball->STATE::SHOT);

	//	if (DontDestroy->GameMode_ != 3)
	//		ball->SetMaterial();
	//}
}