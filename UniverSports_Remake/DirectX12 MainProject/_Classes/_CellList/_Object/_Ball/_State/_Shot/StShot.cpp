#include "StShot.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_CellList/_Object/_Ball/_State/_Float/StFloat.h"
#include "DontDestroyOnLoad.h"

void StShot::Initialize() {
	myState_ = B_STATE::SHOT;
}

void StShot::Update(ObjBall* ball) {
	const float _pos_z = std::min(0.0f, ball->myPosZ() + 0.064f);
	const XMFLOAT2& _pos = ball->myPosition();
	ball->AssignTransform(XMFLOAT3(_pos.x, _pos.y, _pos_z), XMFLOAT2(0.0f, 0.0f));

	const bool _isFieldOut = FIELD::IsOut(_pos, GAME_CONST.BA_SCALE);
	const bool _isGotStuck = std::abs(position_.x) == FIELD::SIDE_X;

	if (_isFieldOut || _isGotStuck || ball->IsBreaked() || (ball->GetOwnerID() == -1)) {
		ball->FlagResets();
		ball->SetOwnerID(-1);
		StFloat* flo = new StFloat();
		ball->SwitchState(flo);
		ball->SwitchColor(ObjBall::COLOR_TYPE::DEFAULT_COLOR);
	}
}