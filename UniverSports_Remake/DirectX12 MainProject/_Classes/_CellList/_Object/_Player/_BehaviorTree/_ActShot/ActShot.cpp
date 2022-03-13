#include "ActShot.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"

void ActShot::Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player) {
	if (!player.HasBall())
		return;

	if (Press.ShotKey(player.myObjectID())) {

	}
}

void ActShot::Update(const float deltaTime, ObjPlayer& player) {
	if (!player.HasBall())
		return;
}

bool ActShot::ActShot::Think(ObjPlayer& player) {
	return true;
}