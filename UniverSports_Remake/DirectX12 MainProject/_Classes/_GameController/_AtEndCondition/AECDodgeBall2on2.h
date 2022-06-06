/**
 * @file AECDodgeBall2on2.h
 * @brief �h�b�W�{�[��2on2���[�h�̏I�������N���X
 * @author �V���D�F
 * @date 2021/06/04
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "AtEndCondition.h"
#include "DontDestroyOnLoad.h"

class AECDodgeBall2on2 : public AtEndCondition {
public:
	AECDodgeBall2on2() {}
	virtual ~AECDodgeBall2on2() {}

	/**
	* @brief �Q�[�����I����������Ԃ�
	* @return �Q�[���̏I�����
	*/
	virtual bool IsFined() override { return DontDestroy->Survivor_.RemainingOfTeam() <= 1; }
};