#include "StFloat.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"

void StFloat::Initialize() {
	std::random_device _seed;
	randomEngine	= std::mt19937(_seed());
	limit_pos_x		= (DontDestroy->GameMode_ != 3) ? GAME_CONST.FieldSide_X : 5.5f;
	limit_pos_y		= (DontDestroy->GameMode_ != 3) ? GAME_CONST.FieldSide_Y : 5.5f;
	limit_direct_x	= DIRECT_X[DontDestroy->GameMode_ / 3];
	limit_direct_y	= DIRECT_Y[DontDestroy->GameMode_ / 3];

	SetTransform();
}

void StFloat::Update(ObjBall* ball) {
	if (ball->IsBreaked()) {
		ball->FlagResets();
		ReSpone(ball);
	}

	if (ball->IsInPlayerHands()) {
		ball->ResetVelocity();
		ball->SwitchState(ball->STATE::CAUTCH);
		ball->SwitchColor(ball->COLOR_TYPE::PLAYERS_COLOR);
		return;
	}

	if (DontDestroy->GameMode_ != 3)
		CheckFieldOut(ball);
	else
		LoopPos(ball);
}

void StFloat::SetTransform() {
	position_	= RandomPosition();
	forward_	= RandomForward(position_);
}

void StFloat::ReSpone(ObjBall* ball) {
	SetTransform();
	ball->AssignTransform(Vector3(position_.x, position_.y, 0.0f), forward_);
	ball->AddPower(Vector3(forward_.x, forward_.y, 0.0f), GAME_CONST.BA_SPEED_FLOAT);
}

SimpleMath::Vector2 StFloat::RandomPosition() {
	pos_start_x		= std::uniform_int_distribution<>(-limit_pos_x, limit_pos_x);
	int _random_x	= pos_start_x(randomEngine);
	int _random_y;

	if (std::abs(_random_x) == limit_pos_x) {
		pos_start_y = std::uniform_int_distribution<>(-limit_pos_y - GAME_CONST.BA_SCALE, limit_pos_y + GAME_CONST.BA_SCALE);
		_random_y	= pos_start_y(randomEngine);
	}
	else {
		pos_start_y = std::uniform_int_distribution<>(0, 2);
		_random_y	= pos_start_y(randomEngine);
		_random_y	= _random_y == 0 ? -limit_pos_y - GAME_CONST.BA_SCALE : limit_pos_y + GAME_CONST.BA_SCALE;
	}

	return Vector2(_random_x, _random_y);
}

SimpleMath::Vector2 StFloat::RandomForward(const SimpleMath::Vector2 position) {
	direct_x					 = std::uniform_real_distribution<float>(-limit_direct_x, limit_direct_x);
	direct_y					 = std::uniform_real_distribution<float>(-limit_direct_y, limit_direct_y);
	const float _direct_x		 = direct_x(randomEngine);
	const float _direct_y		 = direct_y(randomEngine);
	SimpleMath::Vector2 _forward = SimpleMath::Vector2(_direct_x, _direct_y);

	_forward					 = _forward - position;
	_forward.Normalize();

	return _forward;
}


void StFloat::CheckFieldOut(ObjBall* ball) {
	if (ball->IsFieldOut(ball->myPosition(), GAME_CONST.BA_SCALE) || (std::abs(position_.x) == GAME_CONST.FieldSide_X))
		ReSpone(ball);
}

void StFloat::LoopPos(ObjBall* ball) {
	if (ball->IsFieldOut(position_, 0.0f)) {
		ball->ClampLoop(position_);
		//ball->SetBtPosition(position_);
	}
}