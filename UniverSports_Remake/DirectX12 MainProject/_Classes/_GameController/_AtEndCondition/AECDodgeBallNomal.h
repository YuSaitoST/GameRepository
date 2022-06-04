/**
 * @file AECDodgeBallNomal.h
 * @brief �h�b�W�{�[���m�[�}�����[�h�̏I�������N���X
 * @author �V���D�F
 * @date 2021/06/04
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "AtEndCondition.h"
#include "DontDestroyOnLoad.h"

class AECDodgeBallNomal : public AtEndCondition {
public:
	AECDodgeBallNomal() {}
	virtual ~AECDodgeBallNomal() {}

	virtual bool IsFined() override { return DontDestroy->Survivor_.RemainingNumberOfPlayer() <= 1; }
};