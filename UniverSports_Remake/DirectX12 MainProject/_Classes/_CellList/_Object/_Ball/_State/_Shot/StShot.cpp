#include "StShot.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "DontDestroyOnLoad.h"

void StShot::Update(ObjBall* ball) {
	pos_z_ = std::min(0.0f, ball->myPosZ() + 0.016f);
	const Vector2 &_pos = ball->myPosition();
	ball->AssignTransform(Vector3(_pos.x, _pos.y, pos_z_), forward_);

	const bool _isFieldOut = ball->IsFieldOut(ball->myPosition(), GAME_CONST.BA_SCALE);
	const bool _isGotStuck = std::abs(position_.x) == GAME_CONST.FieldSide_X;

	if (_isFieldOut || _isGotStuck || ball->IsBreaked() || ball->GetOwnerID() == -1) {
		ball->SetOwnerID(-1);
		ball->SwitchColor(ObjBall::COLOR_TYPE::DEFAULT_COLOR);
		ball->SwitchState(ObjBall::STATE::FLOAT);
	}
}