/**
 * @file CellList.h
 * @brief ��ԃ��X�g�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Object/ObjectBase.h"

// �O���錾
class Cell;

// ��ԃ��X�g�N���X
class CellList {
public:
	CellList();
	virtual ~CellList();

	void PushList(Cell* cp);
	ObjectBase* GetCollision(int index, ObjectBase* m);

private:
	//! �������x���̍ő�l
	const int N = 2;

	//! ���`��ԃ��X�g
	Cell* cpList_;

};