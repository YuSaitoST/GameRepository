/**
 * @file PlayerList.h
 * @brief プレイヤーのリストクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <vector>
#include "ObjPlayer.h"

//前方宣言
class BallsInstructor;

class PlayerList {
public:
	PlayerList();
	virtual ~PlayerList();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void RenderModel();
	void RenderSprite();
	void RenderTransparency();

	void AddWorld(btDynamicsWorld* physics_world_);
	void RemoveWorld(btDynamicsWorld* physics_world_);

	void SetInstructors(BallsInstructor* blInstructor, PlayersInstructor* plInstuructor);

	// MainScene::Render()内IconAnimator::Render()に用いる
	int PlayerLife(int index);

	// StCautch::Update()内で用いる
	XMFLOAT2 PlayerHandsPos(int index);

	std::vector<ObjPlayer*> GetList() const { return list_; }

private:
	static const int N_PLAYER = 4;

	const XMFLOAT3 POS_START[N_PLAYER] = {
		XMFLOAT3(-GAME_CONST.PL_POS_X, GAME_CONST.PL_POS_Y, 0.0f),
		XMFLOAT3(GAME_CONST.PL_POS_X,	GAME_CONST.PL_POS_Y, 0.0f),
		XMFLOAT3(-GAME_CONST.PL_POS_X, -GAME_CONST.PL_POS_Y, 0.0f),
		XMFLOAT3(GAME_CONST.PL_POS_X,  -GAME_CONST.PL_POS_Y, 0.0f)
	};

private:
	std::vector<ObjPlayer*> list_;
};