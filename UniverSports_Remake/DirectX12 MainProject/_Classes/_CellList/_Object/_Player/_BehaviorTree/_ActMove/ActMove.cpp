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
	
	if (!my.HasBall()) {
		target_pos_new_ = ObjectManager::TheClosestBallPos(my.myPosition());
		const float _angle = AngleOf2Vector((target_pos_new_ - my.myPosition()), (target_pos_old_ - my.myPosition()));
		if (std::fabsf(_angle) < 0.13f)
			return false;
		direction_ = target_pos_new_ - my.myPosition();
		direction_.Normalize();
		return true;
	}
	else if (my.HasBall()) {
		target_pos_new_ = ObjectManager::TheClosestPlayerPosition(my.myPosition(), _comparison);
		const float _angle = AngleOf2Vector((target_pos_new_ - my.myPosition()), (target_pos_old_ - my.myPosition()));
		if (std::fabsf(_angle) < 0.13f)
			return false;
		if (_comparison <= GAME_CONST.PL_AIMING_DISTANCE) {
			direction_ = target_pos_new_ - my.myPosition();
			direction_.Normalize();
			return true;
		}
	}
	//else {
	//	target_pos_new_ = ObjectManager::TheClosestPlayerPosition(my.myPosition(), _comparison);
	//	direction_ = target_pos_new_ - my.myPosition();
	//	direction_.Normalize();
	//	return true;
	//}
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