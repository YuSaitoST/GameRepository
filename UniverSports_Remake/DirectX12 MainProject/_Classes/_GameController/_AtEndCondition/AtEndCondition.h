/**
 * @file AtEndCondition.h
 * @brief �Q�[���̏I�������̊��N���X
 * @author �V���D�F
 * @date 2021/06/04
 */

#pragma once

//�O���錾
class CountTimer;

class AtEndCondition {
public:
	AtEndCondition() {}
	virtual ~AtEndCondition() {}

	virtual bool IsFined(CountTimer* timer) = 0;
};