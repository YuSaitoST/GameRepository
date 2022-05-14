#include "ActShot.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"

void ActShot::Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player) {
	if (!player.HasBall())
		return;

	if (Press.ShotKey(player.myObjectID()))
		player.Shoting(player.MyBallID());
}

void ActShot::Update(const float deltaTime, ObjPlayer& player) {
	// ƒ{[ƒ‹‚ð“Š‚°‚éŠÔŠu‚ð‚ ‚¯‚é
	timer_->Update(deltaTime);
	if (timer_->TimeOut()) {
		player.AsjustmentForward();
		player.Shoting(player.MyBallID());
		timer_->ResetCountTime();
	}
}

bool ActShot::Think(ObjPlayer& player) {
	return player.HasBall();
}