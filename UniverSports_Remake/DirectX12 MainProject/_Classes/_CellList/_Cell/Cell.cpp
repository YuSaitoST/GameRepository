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

	// ���[�g��Ԃ܂�
	for (int _i = (numbers_.Level_ - 1); 0 <= _i; _i--) {
		_m = (_m - 1) >> 2;  // Index���擾

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

/**
* @brief ���̂����������ԂƂ��̏㉺��Ԃ�T�����A�Փ˂������̂�Ԃ�
* @return �Փ˂�������
*/
ObjectBase* Cell::GetCollision() {
	ObjectBase* _mr = nullptr;

	// �����x���T��
	_mr = cellList.GetCollision(numbers_.MsIndex_, mp_);
	if (_mr != nullptr)
		return _mr;

	// ����T��
	_mr = UpperSearch();
	if (_mr != nullptr)
		return _mr;

	// �����T��
	_mr = LowerSearch(numbers_.MsIndex_);
	
	return _mr;
}

/**
* @brief �o�������X�g���甲����
*/
void Cell::Remove() {
	this->next_->prev_ = this->prev_;
	this->prev_->next_ = this->next_;
}

/**
* @brief �������镨�̂̍��W�ɍ��킹�ċ�Ԃ��X�V
*/
void Cell::UpdateToMorton() {
	Remove();
	BitCalculation::MoverToMorton(mp_->myPosition(), mp_->myRadian(), numbers_);
	cellList.PushList(this);
}