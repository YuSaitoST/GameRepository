/**
 * @file OpeClose.h
 * @brief ��������摜�̔�\���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_UI/_OperateUI/_StateOpe/StateOpeBase.h"

class OpeClose : public OP_StateBase {
public:
	OpeClose() {};
	virtual ~OpeClose() {};

	virtual void Initialize() override;
	virtual void Update(const float deltaTime, OperateUI* operate) override;
};