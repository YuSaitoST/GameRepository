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

	//�ړ�
	_pos += _direction * BALL_PARAM.SPEED_GOAL;

	//�ʒu�̒����i�S�[���̊p�ɍ����悤�Ɂj
	_pos += _direction * XMFLOAT2(_scale, _scale);
	FIELD::Clamp(_pos);
	_pos -= _direction * XMFLOAT2(_scale, _scale);
	
	//���W�̐ݒ�
	ball->SetPhysicsTransform(XMFLOAT3(_pos.x, _pos.y, ball->myPosZ()), _direction);

	//�L���b�`���ꂽ���ԕω�
	if (ball->IsInPlayerHands()) {
		std::unique_ptr<StCautch> _cautch = std::make_unique<StCautch>();
		ball->SwitchState(_cautch.release());
		return;
	}
}