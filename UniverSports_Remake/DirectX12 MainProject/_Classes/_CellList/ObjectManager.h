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
#include "_Object/_Wire/WireList.h"
#include "_PlayersInstructor/PlayersInstructor.h"

//! 空間リスト
extern CellList cellList;

class ObjectManager {
public:
	ObjectManager();
	virtual ~ObjectManager() {}

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void RenderModels();
	void RenderSprites();
	void RenderAlphas();

	void AddWorld(btDynamicsWorld* physics_world_);
	void RemoveWorld(btDynamicsWorld* physics_world_);

private:
	std::unique_ptr<PlayerList>		playerList_;	//! プレイヤーリスト
	std::unique_ptr<BallList>		ballList_;		//! ボールリスト
	std::unique_ptr<WireList>		wireList_;		//! ワイヤーリスト
	std::unique_ptr<IconAnimator>	icon_animator_;	//! 残機アイコン

	DX9::MODEL mod_ball_;	//! ボールのモデル
};