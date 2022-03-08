#include "StFloat.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"

StFloat::StFloat()  {

}

StFloat::~StFloat() {

}

void StFloat::Initialize() {
	std::random_device _seed;
	randomEngine = std::mt19937(_seed());
	limit_pos_x = (DontDestroy->GameMode_ != 3) ? GAME_CONST.FieldSide_X : 5.5f;
	limit_pos_y = (DontDestroy->GameMode_ != 3) ? GAME_CONST.FieldSide_Y : 5.5f;
}

void StFloat::Update(const float deltaTime, ObjBall* ball) {
	if (ball->IsFieldOut(ball->myPosition(), 1.0f)) {
		SimpleMath::Vector2& forward = ball->myDirection();
		ReSpone(ball->myPosition(), forward);
		ball->AddPower(Vector3(forward.x, forward.y, 0.0f), GAME_CONST.BA_SPEED_FLOAT);
	}
}

void StFloat::ReSpone(SimpleMath::Vector2& position, SimpleMath::Vector2& forward) {
	position = RandomPosition();

	if (DontDestroy->GameMode_ != 3)
		forward = RandomDirection(position);
}

SimpleMath::Vector2 StFloat::RandomPosition() {
	pos_start_x = std::uniform_int_distribution<>(-limit_pos_x, limit_pos_x);
	int _random_x = pos_start_x(randomEngine);
	int _random_y;

	if (std::abs(_random_x) == limit_pos_x) {
		pos_start_y = std::uniform_int_distribution<>(-limit_pos_y - GAME_CONST.BA_SCALE, limit_pos_y + GAME_CONST.BA_SCALE);
		_random_y = pos_start_y(randomEngine);
	}
	else {
		pos_start_y = std::uniform_int_distribution<>(0, 2);
		_random_y = pos_start_y(randomEngine);
		_random_y = _random_y == 0 ? -limit_pos_y - GAME_CONST.BA_SCALE : limit_pos_y + GAME_CONST.BA_SCALE;
	}

	return SimpleMath::Vector2(_random_x, _random_y);
}

SimpleMath::Vector2 StFloat::RandomDirection(SimpleMath::Vector2 pos) {
	direct_x = std::uniform_real_distribution<float>(-5.5f, 5.5f);
	direct_y = std::uniform_real_distribution<float>(-5.5f, 5.5f);
	const float _direct_x = direct_x(randomEngine);
	const float _direct_y = direct_y(randomEngine);
	auto _forward = SimpleMath::Vector2(_direct_x, _direct_y);

	auto _start = pos;
	auto _end = _forward;
	_forward = _end - _start;
	_forward.Normalize();

	return _forward;
}