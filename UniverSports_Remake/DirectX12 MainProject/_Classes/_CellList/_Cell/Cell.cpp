#include "Cell.h"
#include "_Classes/_CellList/ObjectManager.h"

Cell::Cell() {
	numbers_	= -1;
	mp_			= nullptr;
	next_		= prev_ = this;
}

Cell::Cell(ObjectBase* m) {
	numbers_	= -1;
	mp_			= m;
	next_		= prev_ = this;
	BitCalculation::MoverToMorton(mp_->myPosition(), mp_->myRadian(), numbers_);
}

Cell::~Cell() {
	
}

ObjectBase* Cell::UpperSearch() {
	int _m = numbers_.MsIndex_;
	ObjectBase* _mr = nullptr;

	// ルート空間まで
	for (int _i = (numbers_.Level_ - 1); 0 <= _i; _i--) {
		_m = (_m - 1) >> 2;  // Indexを取得

		// _mの空間に対して衝突判定
		_mr = cellList.GetCollision(_m, this->mp_);
		if (_mr != nullptr)
			return _mr;
	}

	return nullptr;
}

ObjectBase* Cell::LowerSearch(int nr) {
	ObjectBase* _mr = nullptr;

	// 指定されたIndex(nr)の空間に対して衝突判定
	_mr = cellList.GetCollision(nr, this->mp_);
	if (_mr != nullptr)
		return _mr;

	nr = nr * 4 + 1;

	// 下位空間4つ全て回る
	for (int _i = 0, _n = BitCalculation::GetIndex(BitCalculation::DivisionLevel + 1, 0); _i < 4; _i++) {
		// 最大数を超えてなければ、再起して最大分割レベルまで判定
		if (nr + _i < _n) {
			_mr = LowerSearch(nr + _i);
			if (_mr != nullptr)
				return _mr;
		}
		else {
			break;
		}
	}

	return nullptr;
}

/**
* @brief 物体が所属する空間とその上下空間を探索し、衝突した物体を返す
* @return 衝突した物体
*/
ObjectBase* Cell::GetCollision() {
	ObjectBase* _mr = nullptr;

	// 同レベル探索
	_mr = cellList.GetCollision(numbers_.MsIndex_, mp_);
	if (_mr != nullptr)
		return _mr;

	// 上方探索
	_mr = UpperSearch();
	if (_mr != nullptr)
		return _mr;

	// 下方探索
	_mr = LowerSearch(numbers_.MsIndex_);
	
	return _mr;
}

/**
* @brief 双方向リストから抜ける
*/
void Cell::Remove() {
	this->next_->prev_ = this->prev_;
	this->prev_->next_ = this->next_;
}

/**
* @brief 所属する物体の座標に合わせて空間を更新
*/
void Cell::UpdateToMorton() {
	Remove();
	BitCalculation::MoverToMorton(mp_->myPosition(), mp_->myRadian(), numbers_);
	cellList.PushList(this);
}