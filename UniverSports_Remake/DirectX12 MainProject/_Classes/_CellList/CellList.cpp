#include "CellList.h"
#include "_Cell/Cell.h"
#include "_Classes/_CellList/_BitCalculation/BitCalculation.h"
#include <cassert>

CellList::CellList() {
	cpList_				= new Cell[BitCalculation::GetIndex(N + 1, 0)];
}

CellList::~CellList() {
	delete[] cpList_;
}

/**
* @brief ��Ԃ�o�^����
* @param cp ���
*/
void CellList::PushList(Cell* cp) {
	int _m				= cp->numbers_.MsIndex_;
	int _iMax			= BitCalculation::GetIndex(N + 1, 0);

	assert((0 <= _m) && (_m < _iMax) + "CellList::PushList : ��ԃ��X�g�O�ł�");

	cp->next_			= cpList_[_m].next_;		// �����̎���Cell��o�^
	cp->prev_			= &cpList_[_m];				// ������Cell�̎Q�Ƃ�o�^
	cp->next_->prev_	= cp->prev_->next_ = cp;	// �u�����̎��̑O�v�Ɓu�����̑O�̎��v�Ɏ�����Cell��o�^
}

/**
* @brief �w�肵����ԓ��ł̏Փ˔���
* @param index ��Ԃ̃C���f�b�N�X
* @param m �Փˏ�Ԃ𒲂ׂ�������
* @return �Փ˂�������(�Փ˂��Ă��Ȃ��ꍇ��nullptr)
*/
ObjectBase* CellList::GetCollision(int index, ObjectBase* m) {
	ObjectBase* _mp_opponent = nullptr;

	// �w�肵��index�̋�ԓ�
	for (Cell* _cp = cpList_[index].next_, *_np = nullptr;
		_cp != &cpList_[index];) 
	{
		_np = _cp->next_;

		_mp_opponent = m->GetCollision(_cp->mp_);

		if (_mp_opponent != nullptr && m != _mp_opponent) {
			// ������ޓ��m�̏Փ˂Ȃ疳��
			if (m->myObjectType() == _cp->mp_->myObjectType())
				continue;

			return _mp_opponent;
		}

		_cp = _np;
	}

	return nullptr;
}