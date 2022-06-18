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
* @brief ‹óŠÔ‚ð“o˜^‚·‚é
* @param cp ‹óŠÔ
*/
void CellList::PushList(Cell* cp) {
	int _m				= cp->numbers_.MsIndex_;
	int _iMax			= BitCalculation::GetIndex(N + 1, 0);

	assert((0 <= _m) && (_m < _iMax) + "CellList::PushList : ‹óŠÔƒŠƒXƒgŠO‚Å‚·");

	cp->next_			= cpList_[_m].next_;		// Ž©•ª‚ÌŽŸ‚ÌCell‚ð“o˜^
	cp->prev_			= &cpList_[_m];				// Ž©•ª‚ÌCell‚ÌŽQÆ‚ð“o˜^
	cp->next_->prev_	= cp->prev_->next_ = cp;	// uŽ©•ª‚ÌŽŸ‚Ì‘Ov‚ÆuŽ©•ª‚Ì‘O‚ÌŽŸv‚ÉŽ©•ª‚ÌCell‚ð“o˜^
}

/**
* @brief Žw’è‚µ‚½‹óŠÔ“à‚Å‚ÌÕ“Ë”»’è
* @param index ‹óŠÔ‚ÌƒCƒ“ƒfƒbƒNƒX
* @param m Õ“Ëó‘Ô‚ð’²‚×‚½‚¢•¨‘Ì
* @return Õ“Ë‚µ‚½•¨‘Ì(Õ“Ë‚µ‚Ä‚¢‚È‚¢ê‡‚Ínullptr)
*/
ObjectBase* CellList::GetCollision(int index, ObjectBase* m) {
	ObjectBase* _mp_opponent = nullptr;

	// Žw’è‚µ‚½index‚Ì‹óŠÔ“à
	for (Cell* _cp = cpList_[index].next_, *_np = nullptr;
		_cp != &cpList_[index];) 
	{
		_np = _cp->next_;

		_mp_opponent = m->GetCollision(_cp->mp_);

		if (_mp_opponent != nullptr && m != _mp_opponent) {
			// “¯‚¶Ží—Þ“¯Žm‚ÌÕ“Ë‚È‚ç–³Ž‹
			if (m->myObjectType() == _cp->mp_->myObjectType())
				continue;

			return _mp_opponent;
		}

		_cp = _np;
	}

	return nullptr;
}