#include "BallsInstructor.h"
#include "_Classes/_CellList/ObjectManager.h"

/**
* @brief キャッチ指示
*/
void BallsInstructor::BallCautch(const int playerID, const int ballID) {
	ObjectManager::Access(ballID)->WasCaught(playerID);
}

/**
* @brief 投げ指示
*/
void BallsInstructor::BallShot(const int ballID, DirectX::SimpleMath::Vector2 forward) {
	ObjectManager::Access(ballID)->WasThrown(forward);
}

/**
* @brief 投げられたボールの削除指示
*/
void BallsInstructor::BallBreakOfThrower(const int ballID) {
	ObjectManager::Access(ballID)->WasGuessed();
}

/**
* @brief 所持されてるボールの削除指示
*/
void BallsInstructor::BallBreakOfTheHitter(const int ballID) {
	ObjectManager::Access(ballID)->BallBreak();
}