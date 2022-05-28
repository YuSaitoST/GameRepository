#include "StShot.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "DontDestroyOnLoad.h"

void StShot::Initialize() {
	myState_ = B_STATE::SHOT;
}

void StShot::Update(ObjBall* ball) {
	const float _pos_z = std::min(0.0f, ball->myPosZ() + 0.016f);
	const Vector2 &_pos = ball->myPosition();
	ball->AssignTransform(Vector3(_pos.x, _pos.y, _pos_z), forward_);

	const bool _isFieldOut = FIELD::IsOut(_pos, GAME_CONST.BA_SCALE);
	const bool _isGotStuck = (std::abs(position_.x) == FIELD::SIDE_X)/* || (position_.x == 1.0f)*/;

	if (_isFieldOut || _isGotStuck || ball->IsBreaked() || (ball->GetOwnerID() == -1)) {
		ball->FlagResets();
		ball->SetOwnerID(-1);
		ball->SwitchColor(ObjBall::COLOR_TYPE::DEFAULT_COLOR);
		ball->SwitchState(B_STATE::FLOATING);
	}
}