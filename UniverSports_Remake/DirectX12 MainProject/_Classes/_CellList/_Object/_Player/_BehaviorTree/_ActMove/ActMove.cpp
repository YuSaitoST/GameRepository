#include "ActMove.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_CellList/ObjectManager.h"

void ActMove::Initialize(int id) {

}

void ActMove::LoadAssets() {

}

void ActMove::Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player) {
	const Vector2 power = direction * GAME_CONST.Move_FirSpeed * 0.25f * deltaTime;
	player.Moving(Vector3(power.x, power.y, 0.0f));
	player.AssignPosition();
}

void ActMove::Update(const float deltaTime, ObjPlayer& player) {
	const SimpleMath::Vector2 _closestPlayerPos = ObjectManager::TheClosestPlayerPos(player.myPosition());
	direction_ = _closestPlayerPos - player.myPosition();
	direction_.Normalize();

	const Vector2 power = direction_ * GAME_CONST.Move_FirSpeed * 0.25f * deltaTime;
	player.Moving(Vector3(power.x, power.y, 0.0f));
	player.AssignPosition();
}

bool ActMove::Think(ObjPlayer& my) {
	// ëºÇÃObjectBaseÉNÉâÉXÇéQè∆Ç≈Ç´ÇÈÇÊÇ§Ç…ÇµÇΩÇ¢
	return true;
}