#include "BallsInstructor.h"
#include "_Classes/_CellList/_Object/_Ball/BallList.h"
#include "_Classes/_NearestPosition/NearestPosition.h"

void BallsInstructor::Initialize() {
	for (ObjBall* ball : list_)
		posList_.push_back(&(ball->myPosition()));
}

/**
* @brief アクセスする
* @param ballID ボールのID
* @return ボール
*/
ObjBall* BallsInstructor::Access(const int ballID) const {
	if (ballID < 0)
		return nullptr;

	return list_[ballID];
}

/**
* @brief キャッチ指示
* @param playerID プレイヤーのID
* @param ballID ボールのID
*/
void BallsInstructor::Cautch(const int playerID, const int ballID) {
	list_[ballID]->WasCaught(playerID);
}

/**
* @brief 投げ指示
* @param ballID ボールのID
*/
void BallsInstructor::Shot(const int ballID, DirectX::SimpleMath::Vector2 forward) {
	list_[ballID]->WasThrown(forward);
}

/**
* @brief 投げられたボールの削除指示
* @param ballID ボールのID
*/
void BallsInstructor::BreakOfThrower(const int ballID) {
	list_[ballID]->WasGuessed();
}

/**
* @brief 所持されてるボールの削除指示
* @param ballID ボールのID
*/
void BallsInstructor::BreakOfTheHitter(const int ballID) {
	list_[ballID]->BallBreak();
}

/**
* @brief 一番近いボールを返す
* @param myPosition 自身の座標
* @return 一番近いボール
*/
ObjBall* BallsInstructor::GetNearestBall(DirectX::XMFLOAT2 myPosition) {
	return Access(PosCheck::GetNearestObjectID(posList_, myPosition));
}