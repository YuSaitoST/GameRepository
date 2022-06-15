#include "StGoal.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_CellList/_Object/_Ball/_State/_Cautch/StCautch.h"

void StGoal::Initialize() {
	myState_ = B_STATE::GOAL;
}

void StGoal::Update(ObjBall* ball) {

	//if (ball->IsFieldOut(position_, 0.0f)) {
	//	//forward_ = SimpleMath::Vector3::Zero;
	//	//ball->SetForward(forward_);
	//	////ball->SetOwnerID(-1);

	//	//ball->SetBtPosition(SimpleMath::Vector3(99.0f, 99.0f, 0.0f));
		//	// �ړ�����
		//	position_ += forward_ * GAME_CONST.BA_SPEED_SHOT * 0.01f;
		//	//ball->SetBtPosition(position_);
		//}

	//if (!FIELD::IsOut(position_, 1.0f)) {
	//	//position_ += forward_ * GAME_CONST.BA_SPEED_SHOT * 0.01f;
	//}
	//else 
	
	const XMFLOAT2 pos = ball->myPosition();
	ball->SetPhysicsPosition(XMFLOAT3(pos.x, pos.y, 1000.0f));

	if (ball->IsInPlayerHands()) {
		std::unique_ptr<StCautch> cautch = std::make_unique<StCautch>();
		ball->SwitchState(cautch.release());
	}
}