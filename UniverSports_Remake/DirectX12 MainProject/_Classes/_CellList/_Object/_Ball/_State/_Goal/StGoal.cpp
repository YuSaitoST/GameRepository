#include "StGoal.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_CellList/_Object/_Ball/_State/_Cautch/StCautch.h"

void StGoal::Initialize() {
	myState_ = B_STATE::GOAL;
}

void StGoal::Update(ObjBall* ball) {
	Vector2& _pos = ball->myPosition();
	const Vector2 _direction = ball->myDirection();
	const float _scale = ball->myRadian() * 2;

	//移動
	_pos += _direction * BALL_PARAM.SPEED_GOAL;

	//位置の調整（ゴールの角に合うように）
	_pos += _direction * XMFLOAT2(_scale, _scale);
	FIELD::Clamp(_pos);
	_pos -= _direction * XMFLOAT2(_scale, _scale);
	
	//座標の設定
	ball->SetPhysicsTransform(XMFLOAT3(_pos.x, _pos.y, ball->myPosZ()), _direction);

	//キャッチされたら状態変化
	if (ball->IsInPlayerHands()) {
		std::unique_ptr<StCautch> _cautch = std::make_unique<StCautch>();
		ball->SwitchState(_cautch.release());
		return;
	}
}