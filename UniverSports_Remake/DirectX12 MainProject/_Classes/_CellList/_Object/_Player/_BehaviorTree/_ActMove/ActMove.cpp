#include "ActMove.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_CellList/ObjectManager.h"
#include "_Classes/_NearestPosition/NearestPosition.h"
#include "_Classes/_CellList/_BallsInstructor/BallsInstructor.h"

void ActMove::Update(const float deltaTime, Vector2 direction, ObjPlayer& player) {
	const Vector2 power = direction * PLAYER_PARAM.SPEED[player.UseThrasher()] * deltaTime;
	player.Moving(Vector3(power.x, power.y, 0.0f));
	player.AssignPosition();
}

void ActMove::Update(const float deltaTime, ObjPlayer& player) {
	const Vector2 power = direction_ * PLAYER_PARAM.SPEED[0] * deltaTime;
	player.Moving(Vector3(power.x, power.y, 0.0f));
	player.AssignPosition();
}

bool ActMove::Think(ObjPlayer& my) {
	float _comparison = 99.0f;

	DirectX::XMFLOAT2 _myPosition = my.myPosition();
	ObjectBase* _targetPlayer	= my.GetTargetPlayer();
	ObjectBase* _targetBall		= my.GetBallsInstructor()->GetNearestBall(_myPosition);

	if (_targetPlayer != nullptr) {
		if (((ObjPlayer*)_targetPlayer)->HasBall()) {
			// 相手がボールを持っているなら、逃げる方向を決める
			SeekEscapeDirection(_targetPlayer->myDirection());
			return true;
		}
		else if (my.HasBall()) {
			// 投げる方向を決める
			SeekForwardDirection(my.myPosition(), _targetPlayer->myPosition());
			return true;
		}
	}
	
	if (_targetBall != nullptr) {
		if (((ObjBall*)_targetBall)->GetOwnerID() != -1) {
			// 対象のボールが「投げられたボール」なら、逃げる方向を決める
			SeekEscapeDirection(_targetBall->myDirection());
			return true;
		}
		else if (my.HasBall() == 0) {
			// ボールを持っていないなら、ボールを取りに行く
			SeekForwardDirection(my.myPosition(), _targetBall->myPosition());
			return true;
		}
	}

	return false;
}

/**
* @brief 垂直方向を返す
* @param targetDirection 相手の方向
* @return 垂直方向ベクトル
*/
Vector2 ActMove::GetVerticalDirection(Vector2 targetsDirection) {
	return Vector2(-targetsDirection.y, targetsDirection.x);
}

/**
* @brief 逃げる方向ベクトルを算出する
* @param targetPosition 相手の座標
*/
void ActMove::SeekEscapeDirection(Vector2 targetsDirection) {
	direction_ = GetVerticalDirection(targetsDirection);
	const bool _ImOnTop = (0.0f < direction_.y) && (targetsDirection.y < 0.0f);
	const bool _TargetOnTop = (direction_.y < 0.0f) && (0.0f < targetsDirection.y);
	direction_.y *= (_ImOnTop || _TargetOnTop) ? 1 : -1;
	direction_.Normalize();
}

/**
* @brief 移動方向ベクトルを算出する
* @param myPosition 自身の座標
* @param targetPosition 相手の座標
*/
void ActMove::SeekForwardDirection(Vector2 myPosition, Vector2 targetPosition) {
	direction_ = targetPosition - myPosition;
	direction_.Normalize();
}