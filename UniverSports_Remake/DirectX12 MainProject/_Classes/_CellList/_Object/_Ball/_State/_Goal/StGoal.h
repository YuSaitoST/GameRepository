/**
 * @file StGoal.h
 * @brief �{�[���̃S�[����ԃN���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StGoal : public BallState {
public:
	StGoal() {}
	virtual ~StGoal() {}

	virtual void Initialize();
	virtual void Update(ObjBall* ball);
};