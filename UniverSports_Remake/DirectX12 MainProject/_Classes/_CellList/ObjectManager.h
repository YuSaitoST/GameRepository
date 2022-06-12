/**
 * @file ObjectManager.h
 * @brief ���̂̓����N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
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

//! ��ԃ��X�g
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
	std::unique_ptr<PlayerList>		playerList_;	//! �v���C���[���X�g
	std::unique_ptr<BallList>		ballList_;		//! �{�[�����X�g
	std::unique_ptr<WireList>		wireList_;		//! ���C���[���X�g
	std::unique_ptr<IconAnimator>	icon_animator_;	//! �c�@�A�C�R��

	DX9::MODEL mod_ball_;	//! �{�[���̃��f��
};