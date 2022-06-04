/**
 * @file PlayerList.h
 * @brief �v���C���[�̃��X�g�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <vector>
#include "ObjPlayer.h"

//�O���錾
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

	// MainScene::Render()��IconAnimator::Render()�ɗp����
	int PlayerLife(int index);

	// StCautch::Update()���ŗp����
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