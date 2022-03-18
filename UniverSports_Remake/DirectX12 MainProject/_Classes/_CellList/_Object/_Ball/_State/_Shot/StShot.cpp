#include "StShot.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "DontDestroyOnLoad.h"

void StShot::Update(ObjBall* ball) {
	pos_z_ = std::min(0.0f, ball->myPosZ() + 0.016f);
	const auto &_pos = ball->myPosition();
	ball->AssignTransform(Vector3(_pos.x, _pos.y, pos_z_), forward_);

	if (ball->IsFieldOut(ball->myPosition(), GAME_CONST.BA_SCALE) || (std::abs(position_.x) == GAME_CONST.FieldSide_X)) {
		ball->SetOwnerID(-1);
		ball->ResetHandPos();
		ball->SwitchState(ball->STATE::FLOAT);
		ball->SwitchColor(ball->COLOR_TYPE::NOMAL_COLOR);
	}

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