#include "Cell.h"
#include "_Classes/_CellList/ObjectManager.h"
#include "_Classes/_BitCalculation/BitCalculation.h"

Cell::Cell() {
	level_		= -1;
	LsIndex_	= -1;
	MsIndex_	= -1;
	mp_			= nullptr;
	next_		= prev_ = this;
}

Cell::Cell(ObjectBase* m) {
	level_		= -1;
	LsIndex_	= -1;
	MsIndex_	= -1;
	mp_			= m;
	next_		= prev_ = this;
	MoverToMorton(*mp_, level_, LsIndex_, MsIndex_);
}

Cell::~Cell() {

}

ObjectBase* Cell::UpperSearch() {
	int _m = MsIndex_;
	ObjectBase* _mr = nullptr;

	// ルート空間まで
	for (int _i = (level_ - 1); 0 <= _i; _i--) {
		_m = (_m - 1) / 4;  // Indexを取得

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

void Cell::MoverToMorton(ObjectBase& m, int& L, int& I, int& M) {
	// 左上、右下の座標(原点が左上の場合の式)
	Vector2 _UL = Vector2(m.myPosition().x - m.myRadian(), m.myPosition().y + m.myRadian());
	Vector2 _UR = Vector2(m.myPosition().x + m.myRadian(), m.myPosition().y - m.myRadian());

	// それぞれのモートンを代入
	int _mUL = BitCalculation::PointToMorton(_UL);
	int _mUR = BitCalculation::PointToMorton(_UR);

	/* 
		MortonIndexが同じならば、
		最大レベル L = N のどれかのマスに収まっていることになる
			-> 境界をまたいでいない
	*/
	const int _XOR = _mUL ^ _mUR;

	int _k = 0;
	// XORを00が出てくるまでループして、その回った数をKに保存する
	for (int _b = _XOR; _b != 0; _b >>= 2, _k++);

	L = BitCalculation::DivisionLevel - _k;  // KはLと対になる値を表し、この式から分割レベルLが求まる
	I = _mUR >> (2 * _k);
	M = BitCalculation::GetIndex(L, I);

	// _mURを2*Kだけ右シフトする
	// * _mURを使う理由 : I = _mUL^(_mUL^_mUR)>>2k より I = _mUR>>2K (bit演算の性質 a^(a^b)==b を用いている)
}

ObjectBase* Cell::GetCollision() {
	ObjectBase* _mr = nullptr;

	// 同レベル探索
	_mr = cellList.GetCollision(this->MsIndex_, this->mp_);
	if (_mr != nullptr)
		return _mr;

	// 上方探索
	_mr = UpperSearch();
	if (_mr != nullptr)
		return _mr;

	// 下方探索
	_mr = LowerSearch(MsIndex_);
	
	return _mr;
}

//双方向リストから抜ける
void Cell::Remove() {
	this->next_->prev_ = this->prev_;
	this->prev_->next_ = this->next_;
}

// mp_の座標に合わせてモートン符号を更新する
void Cell::UpdateToMorton() {
	Remove();
	MoverToMorton(*mp_, level_, LsIndex_, MsIndex_);  // 所属空間の更新
	cellList.PushList(this);
}