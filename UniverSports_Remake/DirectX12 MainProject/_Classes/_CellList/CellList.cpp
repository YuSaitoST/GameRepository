#include "CellList.h"

CellList::CellList() {
	cpList_				= new Cell[Cell::GetIndex(N + 1, 0)];
}

CellList::~CellList() {
	delete[] cpList_;
}

void CellList::PushList(Cell* cp) {
	int _m				= cp->MsIndex_;
	int _iMax			= Cell::GetIndex(N + 1, 0);

	assert((0 <= _m) && (_m < _iMax));

	cp->next_			= cpList_[_m].next_;		// 自分の次のCellを登録
	cp->prev_			= &cpList_[_m];				// 自分のCellの参照を登録
	cp->next_->prev_	= cp->prev_->next_ = cp;	// 「自分の次の前」と「自分の前の次」に自分のCellを登録
}

//衝突判定(指定されたインデックスの空間内にある物体と判定)
ObjectBase* CellList::IsCollision(int index, ObjectBase* m) {
	ObjectBase* _mp_opponent = nullptr;

	// 指定したindexの空間内
	for (Cell* _cp = cpList_[index].next_, *_np = nullptr;
		_cp != &cpList_[index];) {
		_np = _cp->next_;

		_mp_opponent = m->IsCollision(_cp->mp_);

		if (_mp_opponent != nullptr && m != _mp_opponent) {
			return _mp_opponent;
		}

		_cp = _np;
	}

	return nullptr;
}