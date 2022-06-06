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
	//�i�q��1�ӂɂ����镪����
	const int _CN = (int)std::pow(2, BitCalculation::DivisionLevel);

	//�i�q�̈�ӂ̒���
	const float _sx = FIELD::SIZE_X / _CN;
	const float _sy = FIELD::SIZE_Y / _CN;

	//�i�q�̍��W
	const int _kx = (int)(std::min((pos.x + FIELD::HALF_X), FIELD::SIZE_X) / _sx);
	const int _ky = (int)(std::min((pos.y + FIELD::HALF_Y), FIELD::SIZE_Y) / _sy);

	////�E�[���G���A���ɂ���
	const int _offSideBits = (1 << BitCalculation::DivisionLevel);
	int _clampx = (_kx | _offSideBits); _clampx -= _offSideBits;
	int _clampy = (_ky | _offSideBits); _clampy -= _offSideBits;

	//bit����
	const int _bx = BitSlide(_clampx);
	const int _by = BitSlide(_clampy);

	//OR���Z���ĕԂ�
	return (_bx | (_by << 1));
}

/**
* @brief ��ԃ��x���ƃ��x�����̃C���f�b�N�X���烂�[�g�����������߂�
* @param Level ��ԃ��x��
* @param Index ���x�����̃C���f�b�N�X
* @return ���[�g������
*/
int BitCalculation::GetIndex(int Level, int Index) {
	return (((std::pow(NumberOfDivisions, Level) - 1) / (NumberOfDivisions - 1)) + Index);  //���䋉��
}

/**
* @brief �󂯎������񂩂珊�������Ԃ����߂�
* @param m_pos ���W
* @param radian ���̂̔��a
* @param numbers ��Ԕԍ��Z�b�g
*/
void BitCalculation::MoverToMorton(DirectX::XMFLOAT2 m_pos, float radian, SpaceNumber& numbers) {
	//����A�E���̍��W
	DirectX::XMFLOAT2 _UL = DirectX::XMFLOAT2(m_pos.x - radian, m_pos.y + radian);
	DirectX::XMFLOAT2 _UR = DirectX::XMFLOAT2(m_pos.x + radian, m_pos.y - radian);

	//���ꂼ��̃��[�g������
	int _mUL = PointToMorton(_UL);
	int _mUR = PointToMorton(_UR);

	//XOR
	const int _XOR = _mUL ^ _mUR;

	int _k = 0;
	//XOR��00���o�Ă���܂Ń��[�v���āA���̉��������K�ɕۑ�����
	for (int _b = _XOR; _b != 0; _b >>= 2, _k++);

	numbers.Level_		= DivisionLevel - _k;
	numbers.LsIndex_	= _mUR >> (2 * _k);
	numbers.MsIndex_	= GetIndex(numbers.Level_, numbers.LsIndex_);
}