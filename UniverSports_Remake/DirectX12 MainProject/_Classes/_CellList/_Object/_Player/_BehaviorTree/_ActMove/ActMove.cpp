#include "ActMove.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_CellList/ObjectManager.h"

void ActMove::Update(const float deltaTime, Vector2 direction, ObjPlayer& player) {
	const Vector2 power = direction * GAME_CONST.Move_FirSpeed * 0.25f * deltaTime;
	player.Moving(Vector3(power.x, power.y, 0.0f));
	player.AssignPosition();
}

void ActMove::Update(const float deltaTime, ObjPlayer& player) {
	const Vector2 power = direction_ * GAME_CONST.Move_FirSpeed * 0.25f * deltaTime;
	player.Moving(Vector3(power.x, power.y, 0.0f));
	player.AssignPosition();
}

bool ActMove::Think(ObjPlayer& my) {
	float _comparison = 99.0f;

	ObjectBase* _targetPlayer = ObjectManager::TheClosestPlayer(my.myPosition(), _comparison);
	if (((ObjPlayer*)_targetPlayer)->HasBall()) {
		target_pos_new_ = _targetPlayer->myPosition();
		const Vector2 _target_direction = _targetPlayer->myDirection();
		direction_ = Vector2(-_target_direction.y, _target_direction.x);

		const bool _ImOnTop = (0.0f < direction_.y) && (_target_direction.y < 0.0f);
		const bool _TargetOnTop = (direction_.y < 0.0f) && (0.0f < _target_direction.y);
		direction_.y *= (_ImOnTop || _TargetOnTop) ? 1 : -1;
		direction_.Normalize();
		target_pos_old_ = target_pos_new_;
		return true;
	}
	else {
		if (!my.HasBall())
			target_pos_new_ = ObjectManager::TheClosestBallPos(my.myPosition());
		else
			target_pos_new_ = ObjectManager::TheClosestPlayer(my.myPosition(), _comparison)->myPosition();
		
		//target_pos_old_ = target_pos_new_;
		return ChangeForward(my);
	}
}

float ActMove::GetVectorLenght(Vector2 v) {
	return std::pow((v.x * v.x) + (v.y * v.y), 0.5f);
}

float ActMove::DotProduct(Vector2 v1, Vector2 v2) {
	return (v1.x * v2.x) + (v2.y * v1.y);
}

float ActMove::AngleOf2Vector(Vector2 a, Vector2 b) {
	const float _lenght_a = GetVectorLenght(a);
	const float _lenght_b = GetVectorLenght(b);

	float _cos_sita = DotProduct(a, b) / (_lenght_a * _lenght_b);

	return  std::acosf(_cos_sita);  // ラジアン
	// return (_sita * (180.0f / XM_PI));  // 弧度法
}

bool ActMove::ChangeForward(ObjPlayer& my) {
	if (0.517f < std::fabsf(AngleOf2Vector((target_pos_new_ - my.myPosition()), (target_pos_old_ - my.myPosition())))) {
		direction_ = target_pos_new_ - my.myPosition();
		direction_.Normalize();
		return true;
	}
	else
		return false;
}

bool ActMove::CheckBalls() {
	return false;
}