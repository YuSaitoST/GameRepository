/**
 * @file StStandby.h
 * @brief �{�[���̑ҋ@��ԃN���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StStandby : public BallState {
public:
	StStandby() {}
	virtual ~StStandby() {}

	virtual void Initialize();
	virtual void Update(ObjBall* ball);
};