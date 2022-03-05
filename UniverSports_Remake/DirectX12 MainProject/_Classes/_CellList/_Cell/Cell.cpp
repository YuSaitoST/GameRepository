#include "Cell.h"
#include "MainScene.h"

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
		_mr = cellList.IsCollision(_m, this->mp_);
		if (_mr != nullptr)
			return _mr;
	}

	return nullptr;
}

// 中の動きがよくわからない
ObjectBase* Cell::LowerSearch(int nr) {
	ObjectBase* _mr = nullptr;

	// 指定されたIndex(nr)の空間に対して衝突判定
	_mr = cellList.IsCollision(nr, this->mp_);
	if (_mr != nullptr)
		return _mr;

	// 下位の左上のIndex (?)
	nr = nr * 4 + 1;

	// 下位空間4つ全て回る
	for (int _i = 0, _n = GetIndex(N_ + 1, 0); _i < 4; _i++) {
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

int Cell::BitSlide(int b) {
	b = (b | b << 2) & 0x33;
	b = (b | b << 1) & 0x55;
	return b;
}

int Cell::PointToMorton(Vector2 pos) {
	// 格子の1辺における分割数
	const int _CN = (int)std::pow(2, N_);

	// 格子の一辺の長さ
	const float _sx = 1280.0f / _CN;
	const float _sy = 720.0f / _CN;

	// 格子の座標
	const int _kx = (int)(pos.x / _sx);
	const int _ky = (int)(pos.y / _sy);

	// bit操作
	const int _bx = BitSlide(_kx);
	const int _by = BitSlide(_ky);

	// OR演算して返す
	return (_bx | (_by << 1));
}

void Cell::MoverToMorton(ObjectBase& m, int& L, int& I, int& M) {
	// 左上、右下の座標(原点が左上の場合の式)
	Vector2 _UL = Vector2(m.myPosition().x - m.myRadian(), m.myPosition().y + m.myRadian());
	Vector2 _UR = Vector2(m.myPosition().x + m.myRadian(), m.myPosition().y - m.myRadian());

	// それぞれのモートンを代入
	int _mUL = PointToMorton(_UL);
	int _mUR = PointToMorton(_UR);

	/* 
		MortonIndexが同じならば、
		最大レベル L = N のどれかのマスに収まっていることになる
			-> 境界をまたいでいない
	*/
	const int _XOR = _mUL ^ _mUR;

	int _k = 0;
	// XORを00が出てくるまでループして、その回った数をKに保存する
	for (int _b = _XOR; _b != 0; _b >>= 2, _k++);

	L = N_ - _k;  // KはLと対になる値を表し、この式から分割レベルLが求まる
	I = _mUR >> (2 * _k);
	M = GetIndex(L, I);

	// _mURを2*Kだけ右シフトする
	// * _mURを使う理由 : I = _mUL^(_mUL^_mUR)>>2k より I = _mUR>>2K (bit演算の性質 a^(a^b)==b を用いている)
}

ObjectBase* Cell::IsCollision() {
	ObjectBase* _mr = nullptr;

	// 同レベル探索
	_mr = cellList.IsCollision(this->MsIndex_, this->mp_);
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

// Level,IndexからMortonIndexを求める
int Cell::GetIndex(int Level, int Index) {
	const int _CR = (int)std::pow(4, Level);  // Common ratio (公比)
	return (((_CR - 1) / (4 - 1)) + Index);  // 等比級数
}

// mp_に合わせてモートン符号を更新する
void Cell::UpdateToMorton() {
	Remove();
	MoverToMorton(*mp_, level_, LsIndex_, MsIndex_);  // 所属空間の更新
	cellList.PushList(this);
}