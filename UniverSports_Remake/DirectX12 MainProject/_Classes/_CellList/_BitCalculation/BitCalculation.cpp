#include "BitCalculation.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/_Object/ObjectBase.h"

/**
* @brief �r�b�g��1�����炷
* @param bit �i�q�̍��W
* @return �ϊ������r�b�g�l
*/
int BitCalculation::BitSlide(int bit) {
	bit = (bit | bit << 2) & 0x33;
	bit = (bit | bit << 1) & 0x55;
	return bit;
}

/**
* @brief �󂯎�������W���烂�[�g�����������߂�
* @param pos ���W
* @return ���[�g������
*/
int BitCalculation::PointToMorton(DirectX::XMFLOAT2 pos) {
	//�i�q�̈�ӂ̒���
	const float _sx = (int)FIELD::SIZE_X >> BitCalculation::DivisionLevel;
	const float _sy = (int)FIELD::SIZE_Y >> BitCalculation::DivisionLevel;

	//�i�q�̍��W
	const int _kx = (int)(std::min((pos.x + FIELD::HALF_X), FIELD::SIZE_X) / _sx);
	const int _ky = (int)(std::min((pos.y + FIELD::HALF_Y), FIELD::SIZE_Y) / _sy);

	//�E�[���G���A���ɂ���
	const int _downBit = ~(1 << 2);
	const int _norx = _kx & _downBit;
	const int _nory = _ky & _downBit;

	//OR���Z���ĕԂ�
	return (BitSlide(_norx) | (BitSlide(_nory) << 1));
}

/**
* @brief �󂯎������񂩂珊�������Ԃ����߂�
* @param m_pos ���W
* @param radian ���̂̔��a
* @param numbers ��Ԕԍ��Z�b�g
*/
void BitCalculation::MoverToMorton(DirectX::XMFLOAT2 m_pos, float radian, SpaceNumber& numbers) {
	//����A�E���̍��W
	const DirectX::XMFLOAT2 _UL = DirectX::XMFLOAT2(m_pos.x - radian, m_pos.y + radian);
	const DirectX::XMFLOAT2 _UR = DirectX::XMFLOAT2(m_pos.x + radian, m_pos.y - radian);

	//���ꂼ��̃��[�g������
	const int _mUL = PointToMorton(_UL);
	const int _mUR = PointToMorton(_UR);

	//XOR��00���o�Ă���܂Ń��[�v���āA���̉��������K�ɕۑ�����
	int _k = 0;
	for (int _XOR = _mUL ^ _mUR; _XOR != 0; _XOR >>= 2, _k++);

	//�e�l�̎Z�o
	numbers.Level_		= DivisionLevel - _k;
	numbers.LsIndex_	= _mUR >> (2 * _k);
	numbers.MsIndex_	= GetIndex(numbers.Level_, numbers.LsIndex_);
}