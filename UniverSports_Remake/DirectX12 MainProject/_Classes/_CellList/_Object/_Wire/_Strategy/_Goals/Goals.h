/**
 * @file Goals.h
 * @brief ���C���[�̃S�[���Ƃ��Ă̐U�镑���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Wire/_Strategy/WireStrategy.h"

class Goals : public WireStrategy {
public:
	Goals() {}
	virtual ~Goals() {}

	virtual void Update(ObjWire* wire);

private:

};