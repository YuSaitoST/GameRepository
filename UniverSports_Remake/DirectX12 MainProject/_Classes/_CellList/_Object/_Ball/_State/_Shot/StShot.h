/**
 * @file StShot.h
 * @brief �{�[���̓�����ԃN���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StShot : public BallState {
public:
	StShot() {};
	virtual ~StShot() {}

	virtual void Initialize();
	virtual void Update(ObjBall* ball);
};