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

	// ���[�g��Ԃ܂�
	for (int _i = (level_ - 1); 0 <= _i; _i--) {
		_m = (_m - 1) / 4;  // Index���擾

		// _m�̋�Ԃɑ΂��ďՓ˔���
		_mr = cellList.GetCollision(_m, this->mp_);
		if (_mr != nullptr)
			return _mr;
	}

	return nullptr;
}

ObjectBase* Cell::LowerSearch(int nr) {
	ObjectBase* _mr = nullptr;

	// �w�肳�ꂽIndex(nr)�̋�Ԃɑ΂��ďՓ˔���
	_mr = cellList.GetCollision(nr, this->mp_);
	if (_mr != nullptr)
		return _mr;

	nr = nr * 4 + 1;

	// ���ʋ��4�S�ĉ��
	for (int _i = 0, _n = BitCalculation::GetIndex(BitCalculation::DivisionLevel + 1, 0); _i < 4; _i++) {
		// �ő吔�𒴂��ĂȂ���΁A�ċN���čő啪�����x���܂Ŕ���
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
	// ����A�E���̍��W(���_������̏ꍇ�̎�)
	Vector2 _UL = Vector2(m.myPosition().x - m.myRadian(), m.myPosition().y + m.myRadian());
	Vector2 _UR = Vector2(m.myPosition().x + m.myRadian(), m.myPosition().y - m.myRadian());

	// ���ꂼ��̃��[�g������
	int _mUL = BitCalculation::PointToMorton(_UL);
	int _mUR = BitCalculation::PointToMorton(_UR);

	/* 
		MortonIndex�������Ȃ�΁A
		�ő僌�x�� L = N �̂ǂꂩ�̃}�X�Ɏ��܂��Ă��邱�ƂɂȂ�
			-> ���E���܂����ł��Ȃ�
	*/
	const int _XOR = _mUL ^ _mUR;

	int _k = 0;
	// XOR��00���o�Ă���܂Ń��[�v���āA���̉��������K�ɕۑ�����
	for (int _b = _XOR; _b != 0; _b >>= 2, _k++);

	L = BitCalculation::DivisionLevel - _k;  // K��L�Ƒ΂ɂȂ�l��\���A���̎����番�����x��L�����܂�
	I = _mUR >> (2 * _k);
	M = BitCalculation::GetIndex(L, I);

	// _mUR��2*K�����E�V�t�g����
	// * _mUR���g�����R : I = _mUL^(_mUL^_mUR)>>2k ��� I = _mUR>>2K (bit���Z�̐��� a^(a^b)==b ��p���Ă���)
}

ObjectBase* Cell::GetCollision() {
	ObjectBase* _mr = nullptr;

	// �����x���T��
	_mr = cellList.GetCollision(this->MsIndex_, this->mp_);
	if (_mr != nullptr)
		return _mr;

	// ����T��
	_mr = UpperSearch();
	if (_mr != nullptr)
		return _mr;

	// �����T��
	_mr = LowerSearch(MsIndex_);
	
	return _mr;
}

//�o�������X�g���甲����
void Cell::Remove() {
	this->next_->prev_ = this->prev_;
	this->prev_->next_ = this->next_;
}

// mp_�̍��W�ɍ��킹�ă��[�g���������X�V����
void Cell::UpdateToMorton() {
	Remove();
	MoverToMorton(*mp_, level_, LsIndex_, MsIndex_);  // ������Ԃ̍X�V
	cellList.PushList(this);
}