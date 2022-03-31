#pragma once

#include "_Object/ObjectBase.h"
#include "_Cell/Cell.h"

// ��ԃ��X�g�N���X
class CellList {
public:
	CellList();
	virtual ~CellList();

	void PushList(Cell* cp);  // ���X�g�ɒǉ�
	ObjectBase* GetCollision(int index, ObjectBase* m);  // �Փ˔���	

private:
	const int N = 2;  // �������x���̍ő�
	Cell* cpList_;  // ���`��ԃ��X�g(Cell���܂Ƃ߂�List)
};