/**
 * @file BallList.h
 * @brief �{�[���̃��X�g�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <vector>
#include "ObjBall.h"

class BallList {
public:
	BallList();
	virtual ~BallList();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();
	void AddWorld(btDynamicsWorld* physics_world_);
	void RemoveWorld(btDynamicsWorld* physics_world_);

	/**
	* @brief �{�[�����X�g��Ԃ�
	* @return �{�[�����X�g
	*/
	std::vector<ObjBall*> GetList() const { return list_; }

private:
	std::vector<ObjBall*> list_;
	DX9::MODEL model_;
	int N_BALL;
};