#include "PlayersInstructor.h"
#include "_Classes/_CellList/_Object/_Player/PlayerList.h"
#include "_Classes/_NearestPosition/NearestPosition.h"

void PlayersInstructor::Initialize(const std::vector<ObjPlayer*> playerlist) {
	list_ = playerlist;

	posList_.reserve(list_.size());

	for (ObjPlayer* player : list_)
		posList_.push_back(&(player->myPosition()));
}

/**
* @brief アクセスする
* @param playerID プレイヤーのID
* @return ボール
*/
ObjPlayer* PlayersInstructor::Access(const int playerID) const {
	if (playerID < 0)
		return nullptr;

	return list_[playerID];
}

/**
* @brief 一番近いプレイヤーを返す
* @param myPosition 自身の座標
* @return 一番近いボール
*/
ObjPlayer* PlayersInstructor::GetNearestPlayer(DirectX::XMFLOAT2 myPosition) {
	return Access(PosCheck::GetNearestObjectID(posList_, myPosition));
}

///**
//* @brief 指定したプレイヤーの手元の座標を返す
//* @param index プレイヤーの番号
//* @return 手元の座標
//*/
//DirectX::XMFLOAT2 PlayersInstructor::PlayerHandsPos(const int playerID) {
//	assert((0 <= playerID) && "PlayerInstructor::PlayerHandPos() : 指定したindexが不正です(負の値になっている)");
//	return list_[playerID]->Get_HandPos();
//}