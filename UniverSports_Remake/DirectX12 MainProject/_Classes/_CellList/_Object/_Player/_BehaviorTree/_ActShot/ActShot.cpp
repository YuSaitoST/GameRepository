#include "ActShot.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"

void ActShot::Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player) {
	if (!player.HasBall())
		return;

	if (Press.ShotKey(player.myObjectID()))
		player.Shoting(player.MyBall());
}

void ActShot::Update(const float deltaTime, ObjPlayer& player) {
	timer_->Update(deltaTime);
	if (timer_->TimeOut()) {
		player.Shoting(player.MyBall());
		timer_->ResetCountTime();
	}
}

bool ActShot::ActShot::Think(ObjPlayer& player) {
	return player.HasBall();
}