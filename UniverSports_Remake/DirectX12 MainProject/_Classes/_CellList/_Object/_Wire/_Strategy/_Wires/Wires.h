/**
 * @file Wires.h
 * @brief ���C���[�̃��C���[�Ƃ��Ă̐U�镑���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Wire/_Strategy/WireStrategy.h"

class Wires : public WireStrategy {
public:
	Wires() {}
	virtual ~Wires() {}

	/**
	 * @brief ���C���[�̐U�镑��(�����Ȃ�)
	 * @param wire ���C���[�N���X���g
	*/
	virtual void Update(ObjWire* wire) {}
};