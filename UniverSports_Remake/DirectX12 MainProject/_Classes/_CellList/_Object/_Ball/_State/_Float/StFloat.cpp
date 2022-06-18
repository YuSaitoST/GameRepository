#include "StFloat.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_CellList/_Object/_Ball/_State/_Cautch/StCautch.h"
#include "_Classes/_GameController/GameController.h"

void StFloat::Initialize() {
	std::random_device _seed;
	randomEngine	= std::mt19937(_seed());
	limit_pos_x		= (!DontDestroy->GameMode_.isBILLIARDS()) ? FIELD::HALF_X : 5.5f;
	limit_pos_y		= (!DontDestroy->GameMode_.isBILLIARDS()) ? FIELD::HALF_Y : 5.5f;
	limit_direct_x	= DIRECT_X[DontDestroy->GameMode_.SelectionMode() / 3];
	limit_direct_y	= DIRECT_Y[DontDestroy->GameMode_.SelectionMode() / 3];

	pos_start_x		= std::uniform_real_distribution<float>(-limit_pos_x, limit_pos_x);
	direct_x		= std::uniform_real_distribution<float>(-limit_direct_x, limit_direct_x);
	direct_y		= std::uniform_real_distribution<float>(-limit_direct_y, limit_direct_y);

	myState_		= B_STATE::FLOATING;
}

void StFloat::Update(ObjBall* ball) {
	// 状態変化
	if (ball->IsInPlayerHands()) {
		std::unique_ptr<StCautch> cautch = std::make_unique<StCautch>();
		ball->SwitchState(cautch.release());
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

/**
* @brief リスポーンする処理
* @param ball ボール
*/
void StFloat::ReSpone(ObjBall* ball) {
	XMFLOAT2 forward;
	SetTransform(position_, forward);
	ball->AssignTransform(XMFLOAT3(position_.x, position_.y, 0.0f), forward);
	ball->AddPower(XMFLOAT3(position_.x, position_.y, 0.0f), XMFLOAT3(forward.x, forward.y, 0.0f), BALL_PARAM.SPEED_FLOAT);
	ball->FlagResets();
}

/**
* @brief 座標と方向をセットする
* @param position 座標
* @param forward 方向ベクトル
*/
void StFloat::SetTransform(XMFLOAT2& position, XMFLOAT2& forward) {
	position	= RandomPosition();
	forward		= RandomForward(position);
}

/**
* @brief ランダムで座標を決める
* @return 座標
*/
SimpleMath::Vector2 StFloat::RandomPosition() {
	const float _scale		= BALL_PARAM.MOD_SCALE;
	const float _random_x	= std::min(pos_start_x(randomEngine), FIELD::HALF_X);
	float _random_y			= 0;

	if (std::abs(_random_x) == limit_pos_x) {
		pos_start_y = std::uniform_real_distribution<float>(-limit_pos_y - _scale, limit_pos_y + _scale);
		_random_y	= pos_start_y(randomEngine);
	}
	else {
		pos_start_y = std::uniform_real_distribution<float>(0, 1);
		_random_y	= pos_start_y(randomEngine);
		_random_y	= (_random_y == 0) ? -limit_pos_y - _scale : limit_pos_y + _scale;
	}

	_random_y = std::min(_random_y, FIELD::HALF_Y);

	return Vector2(_random_x, _random_y);
}

/**
* @brief ランダムで方向を決める
* @param position 座標
* @return 方向ベクトル
*/
SimpleMath::Vector2 StFloat::RandomForward(const SimpleMath::Vector2 position) {
	SimpleMath::Vector2 _forward = SimpleMath::Vector2(direct_x(randomEngine), direct_y(randomEngine));
	_forward					 = _forward - position;
	_forward.Normalize();
	return _forward;
}

/**
* @brief 場外に出たらリスポーンする処理
* @param ball ボール
*/
void StFloat::CheckFieldOut(ObjBall* ball) {
	if (FIELD::IsOut(ball->myPosition(), BALL_PARAM.MOD_SCALE) || (std::abs(position_.x) == FIELD::HALF_X)) {
		ReSpone(ball);
	}
}

/**
* @biref 場外に出た時に反対側に出てくる処理
* @param ball ボール
*/
void StFloat::LoopPos(ObjBall* ball) {
	FIELD::ClampLoop(position_);
}