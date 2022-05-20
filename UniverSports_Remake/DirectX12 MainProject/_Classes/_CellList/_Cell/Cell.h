/**
 * @file Serials.h
 * @brief ��ԃN���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

  //------------------------------------------------------------------------------
  //	�C���N���[�h�t�@�C��
  //------------------------------------------------------------------------------
#include "_Classes/_BitCalculation/BitCalculation.h"

//�O���錾
class ObjectBase;

class Cell {
public:
	Cell();
	Cell(ObjectBase* m);
	virtual ~Cell();

	void UpdateToMorton();
	void Remove();
	ObjectBase* GetCollision();

	//" �o�������X�g(�����̑O��̋�Ԃ�����)
	Cell* prev_;
	Cell* next_;

	//! ��Ԃɏ������镨��
	ObjectBase* mp_;

	//! ��Ԕԍ�
	SpaceNumber numbers_;

private:
	ObjectBase* UpperSearch();		  // ��ʒT��
	ObjectBase* LowerSearch(int nr);  // ���ʒT��
};