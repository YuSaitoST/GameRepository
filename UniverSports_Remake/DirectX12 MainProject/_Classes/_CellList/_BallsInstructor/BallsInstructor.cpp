#include "BallsInstructor.h"
#include "_Classes/_CellList/ObjectManager.h"

void BallsInstructor::BallCautch(const int playerID, const int ballID) {
	ObjectManager::Access(ballID)->WasCaught(playerID);
}

void BallsInstructor::BallShot(const int ballID, DirectX::SimpleMath::Vector2 forward) {
	ObjectManager::Access(ballID)->WasThrown(forward);
}

void BallsInstructor::BallBreakOfThrower(const int ballID) {
	ObjectManager::Access(ballID)->WasGuessed();
}

void BallsInstructor::BallBreakOfTheHitter(const int ballID) {
	ObjectManager::Access(ballID)->BallBreak();
}