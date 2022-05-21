/**
 * @file ActShot.h
 * @brief �����˂̍s���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/ActionBase.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

class ActShot final : public ActionBase {
public:
	ActShot() { timer_ = new CountTimer(1.5f);}
	virtual ~ActShot() {}

	virtual void Initialize(int id) {}
	virtual void LoadAssets() {}
	virtual void Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player);
	virtual void Update(const float deltaTime, ObjPlayer& player);
	virtual void UIRender() {}

	virtual bool Think(ObjPlayer& player);

private:
	//! ���𔭎˂���Œ���̊Ԋu���v������^�C�}�[
	CountTimer* timer_;
};