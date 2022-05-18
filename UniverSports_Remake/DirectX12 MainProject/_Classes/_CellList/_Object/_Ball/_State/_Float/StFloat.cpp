#include "StFloat.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_FieldOutCheck/FieldOutCheck.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_GameController/GameController.h"

void StFloat::Initialize() {
	std::random_device _seed;
	randomEngine	= std::mt19937(_seed());
	limit_pos_x		= (!DontDestroy->GameMode_.isBILLIARDS()) ? GAME_CONST.FieldSide_X : 5.5f;
	limit_pos_y		= (!DontDestroy->GameMode_.isBILLIARDS()) ? GAME_CONST.FieldSide_Y : 5.5f;
	limit_direct_x	= DIRECT_X[DontDestroy->GameMode_.SelectionMode() / 3];
	limit_direct_y	= DIRECT_Y[DontDestroy->GameMode_.SelectionMode() / 3];

	pos_start_x		= std::uniform_int_distribution<>(-limit_pos_x, limit_pos_x);
	direct_x		= std::uniform_real_distribution<float>(-limit_direct_x, limit_direct_x);
	direct_y		= std::uniform_real_distribution<float>(-limit_direct_y, limit_direct_y);

	myState_		= B_STATE::FLOATING;

	SetTransform();
}

void StFloat::Update(ObjBall* ball) {
	if (ball->IsInPlayerHands()) {
		ball->SwitchState(B_STATE::CAUTCH);
		ball->SwitchColor(ObjBall::COLOR_TYPE::PLAYERS_COLOR);
		return;
	}

	if (!DontDestroy->GameMode_.isBILLIARDS()) {
		// 通常モードなら、フィールド外に出たらリスポーンする
		CheckFieldOut(ball);
	}
	else {
		// ミニゲームなら、フィールド外に出たら反対側から出てくる(ループする)
		LoopPos(ball);
	}
}

void StFloat::ReSpone(ObjBall* ball) {
	SetTransform();
	ball->AssignTransform(Vector3(position_.x, position_.y, 0.0f), forward_);
	ball->AddPower(Vector3(forward_.x, forward_.y, 0.0f), GAME_CONST.BA_SPEED_FLOAT);
	ball->FlagResets();
}

void StFloat::SetTransform() {
	position_	= RandomPosition();
	forward_	= RandomForward(position_);
}

SimpleMath::Vector2 StFloat::RandomPosition() {
	const int _random_x	= pos_start_x(randomEngine);
	int _random_y		= 0;

	if (std::abs(_random_x) == limit_pos_x) {
		pos_start_y = std::uniform_int_distribution<>(-limit_pos_y - GAME_CONST.BA_SCALE, limit_pos_y + GAME_CONST.BA_SCALE);
		_random_y	= pos_start_y(randomEngine);
	}
	else {
		pos_start_y = std::uniform_int_distribution<>(0, 1);
		_random_y	= pos_start_y(randomEngine);
		_random_y	= (_random_y == 0) ? -limit_pos_y - GAME_CONST.BA_SCALE : limit_pos_y + GAME_CONST.BA_SCALE;
	}

	return Vector2(_random_x, _random_y);
}

SimpleMath::Vector2 StFloat::RandomForward(const SimpleMath::Vector2 position) {
	SimpleMath::Vector2 _forward = SimpleMath::Vector2(direct_x(randomEngine), direct_y(randomEngine));
	_forward					 = _forward - position;
	_forward.Normalize();
	return _forward;
}

void StFloat::CheckFieldOut(ObjBall* ball) {
	if (FIELD::IsOut(ball->myPosition(), GAME_CONST.BA_SCALE) || (std::abs(position_.x) == GAME_CONST.FieldSide_X)) {
		ReSpone(ball);
	}
}

void StFloat::LoopPos(ObjBall* ball) {
	FIELD::ClampLoop(position_);
}