/**
 * @file EffectBase.h
 * @brief �G�t�F�N�g�̊��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "AtEndCondition.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

class AECHandBall : public AtEndCondition {
public:
	AECHandBall() {}
	virtual ~AECHandBall() {}

	/**
	* @brief �Q�[�����I����������Ԃ�
	* @return �Q�[���̏I�����
	*/
	virtual bool IsFined(CountTimer* timer) override { return (timer != nullptr) ? timer->TimeOut() : false; }
};