/**
 * @file AtEndCondition.h
 * @brief �Q�[���̏I�������̊��N���X
 * @author �V���D�F
 * @date 2021/06/04
 */

#pragma once

class AtEndCondition {
public:
	AtEndCondition() {}
	virtual ~AtEndCondition() {}

	virtual bool IsFined() = 0;
};