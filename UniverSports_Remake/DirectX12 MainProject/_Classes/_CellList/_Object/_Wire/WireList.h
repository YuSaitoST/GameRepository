/**
 * @file WireList.h
 * @brief �{�[���̃��X�g�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <vector>
#include "ObjWire.h"

//�O���錾
class BallsInstructor;
class PlayersInstructor;

class WireList {
public:
	WireList();
	virtual ~WireList();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void AddWorld(btDynamicsWorld* physics_world_);
	void RemoveWorld(btDynamicsWorld* physics_world_);

	void SetInstructors(BallsInstructor* blInstructor, PlayersInstructor* plInstuructor);

	/**
	* @brief ���C���[���X�g��Ԃ�
	* @return ���C���[���X�g
	*/
	std::vector<ObjWire*> GetList() const { return list_; }

private:
	std::vector<ObjWire*> list_;
};