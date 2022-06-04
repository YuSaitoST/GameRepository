/**
 * @file PlayersInstructor.h
 * @brief プレイヤー統括クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

//前方宣言
class ObjPlayer;

class PlayersInstructor {
public:
	PlayersInstructor() {}
	virtual ~PlayersInstructor() {}

	void Initialize(const std::vector<ObjPlayer*> playerlist);

	ObjPlayer* Access(const int playerID) const;
	ObjPlayer* GetNearestPlayer(DirectX::XMFLOAT2 myPosition);

	DirectX::XMFLOAT2 PlayerHandsPos(const int playerID);

private:
	std::vector<ObjPlayer*> list_;	//! プレイヤーのリスト
	std::vector<DirectX::SimpleMath::Vector2*> posList_;	//! プレイヤーの座標リスト
};