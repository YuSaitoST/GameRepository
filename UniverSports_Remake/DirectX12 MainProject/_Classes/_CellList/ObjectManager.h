/**
 * @file ObjectManager.h
 * @brief 物体の統括クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/CellList.h"
#include "_Object/ObjectBase.h"
#include "_Object/_Player/ObjPlayer.h"
#include "_Object/_Ball/BallList.h"
#include "_Object/_Wire/ObjWire.h"

//! 空間リスト
extern CellList cellList;

class ObjectManager {
private:
	static const int N_PLAYER	= 4;
	static const int N_WIRE		= 4;

	const Vector3 POS_START[N_PLAYER] = {
		Vector3(-GAME_CONST.PL_POS_X, GAME_CONST.PL_POS_Y, 0.0f),
		Vector3(GAME_CONST.PL_POS_X,	GAME_CONST.PL_POS_Y, 0.0f),
		Vector3(-GAME_CONST.PL_POS_X, -GAME_CONST.PL_POS_Y, 0.0f),
		Vector3(GAME_CONST.PL_POS_X,  -GAME_CONST.PL_POS_Y, 0.0f)
		//Vector3(19, 24, 0.0f),
		//Vector3(45,	24, 0.0f),
		//Vector3(19, 12, 0.0f),
		//Vector3(45, 12, 0.0f)
	};

	const float FX = 32.0f;
	const float FY = 18.0f;
	const float X = FX - 5.25f + 1.25f;
	const float Y = FY - 4.75f + 1.25f;
	//const float FX = 64.0f;
	//const float FY = 32.0f;
	//const float X = 6.5f;
	//const float Y = 6.0f;

	const SimpleMath::Vector3 POS_WIRE[N_WIRE] = {
		Vector3(-X, Y, 0.0f),
		Vector3(X,Y,0.0f),
		Vector3(X,-Y,0.0f),
		Vector3(-X,-Y,0.0f)
		//Vector3(	 X - 2.5f, FY - Y + 3.5f, 0.0f),		//L
		//Vector3(FX - X + 2.5f, FY - Y + 3.5f, 0.0f),			//R
		//Vector3(FX - X + 2.5f,		Y - 1.5f, 0.0f),		//L
		//Vector3(	 X - 2.5f,		Y - 1.5f, 0.0f)				//R
	};

public:
	ObjectManager();
	virtual ~ObjectManager();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void RenderModels();
	void RenderSprites();
	void RenderAlphas();

	void AddWorld(btDynamicsWorld* physics_world_);
	void RemoveWorld(btDynamicsWorld* physics_world_);

	static int PlayerLife(int index);

	static Vector2 PlayerHandsPos(int index);

	static ObjectBase* TheClosestPlayer(const int id, const Vector2 pos, float& comparison);
	static ObjectBase* TheClosestBall(const Vector2 pos, float& comparison);

private:
	static float Distance2Vector(const Vector2 p1, const Vector2 p2);

	//! プレイヤーリスト
	static ObjPlayer* obj_player_[N_PLAYER];
	
	//! ボールリスト
	BallList* ballList_;
	
	//! ワイヤーリスト
	static ObjWire* obj_wire_[N_WIRE];

	//! ボールのモデル
	DX9::MODEL mod_ball_;
};