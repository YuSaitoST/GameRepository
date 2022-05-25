#include "StGoal.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"

void StGoal::Initialize() {
	myState_ = B_STATE::GOAL;
}

void StGoal::Update(ObjBall* ball) {

	//if (ball->IsFieldOut(position_, 0.0f)) {
	//	//forward_ = SimpleMath::Vector3::Zero;
	//	//ball->SetForward(forward_);
	//	////ball->SetOwnerID(-1);

	//	//ball->SetBtPosition(SimpleMath::Vector3(99.0f, 99.0f, 0.0f));
		//	// ˆÚ“®ˆ—
		//	position_ += forward_ * GAME_CONST.BA_SPEED_SHOT * 0.01f;
		//	//ball->SetBtPosition(position_);
		//}

	if (!FIELD::IsOut(position_, 1.0f)) {
		//position_ += forward_ * GAME_CONST.BA_SPEED_SHOT * 0.01f;
	}
	//else if (ball->IsInPlayerHands()) {
	//	ball->SwitchState(B_STATE::CAUTCH);
	//}
}