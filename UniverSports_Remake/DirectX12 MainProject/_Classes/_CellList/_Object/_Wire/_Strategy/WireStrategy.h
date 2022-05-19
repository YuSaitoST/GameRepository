/**
 * @file WireStrategy.h
 * @brief ���C���[�̐U�镑���̊��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

//�O���錾
class ObjWire;

class WireStrategy {
public:
	WireStrategy() {}
	virtual ~WireStrategy() {}

	virtual void Update(ObjWire* wire) = 0;
};