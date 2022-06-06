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
#include "_Classes/_UI/_CharaIcon/IconAnimator.h"
#include "_Classes/_CellList/CellList.h"
#include "_Object/ObjectBase.h"
#include "_Object/_Player/PlayerList.h"
#include "_Object/_Ball/BallList.h"
#include "_Object/_Wire/ObjWire.h"
#include "_PlayersInstructor/PlayersInstructor.h"

//! 空間リスト
extern CellList cellList;

class ObjectManager {
private:
	const float FX = 32.0f;
	const float FY = 18.0f;
	const float X = FX - 5.25f + 1.25f;
	const float Y = FY - 4.75f + 1.25f;

	const SimpleMath::Vector3 POS_WIRE[OBJECT_MAX::WIRE] = {
		Vector3(-X, Y, 0.0f),
		Vector3(X,Y,0.0f),
		Vector3(X,-Y,0.0f),
		Vector3(-X,-Y,0.0f)
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

private:
	//! プレイヤーリスト
	PlayerList* playerList_;
	
	//! ボールリスト
	BallList* ballList_;
	
	//! ワイヤーリスト
	ObjWire* obj_wire_[OBJECT_MAX::WIRE];

	//! プレイヤーのインストラクター
	PlayersInstructor* plInstructor_;
	std::unique_ptr<IconAnimator> icon_animator_;

	//! ボールのモデル
	DX9::MODEL mod_ball_;
};