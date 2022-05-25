#include "BallsInstructor.h"
#include "_Classes/_CellList/_Object/_Ball/BallList.h"

/**
* @brief キャッチ指示
*/
void BallsInstructor::Cautch(const int playerID, const int ballID) {
	list_[ballID]->WasCaught(playerID);
}

/**
* @brief 投げ指示
*/
void BallsInstructor::Shot(const int ballID, DirectX::SimpleMath::Vector2 forward) {
	list_[ballID]->WasThrown(forward);
}

/**
* @brief 投げられたボールの削除指示
*/
void BallsInstructor::BreakOfThrower(const int ballID) {
	list_[ballID]->WasGuessed();
}

/**
* @brief 所持されてるボールの削除指示
*/
void BallsInstructor::BreakOfTheHitter(const int ballID) {
	list_[ballID]->BallBreak();
}