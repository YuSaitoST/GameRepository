#include "StShot.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "DontDestroyOnLoad.h"

void StShot::Initialize() {
	
}

void StShot::Update(ObjBall* ball) {

	//if (DontDestroy->GameMode_ != 3) {
	//	if (ball->IsHit() || ball->IsFieldOut(position_)) {
	//		ball->SetIsShot(false);
	//		ball->SetIsHit(false);
	//		ball->SetOwnerID(-1);
	//		ball->SetBtPosition(SimpleMath::Vector3(99.0f, 99.0f, 0.0f));
	//		ball->SwitchState(ball->STATE::FLOAT);
	//		ball->SetMaterial();
	//	}
	//}
	//else {
	//	ball->SetOwnerID(-1);
	//	ball->SwitchState(ball->STATE::FLOAT);
	//}
}