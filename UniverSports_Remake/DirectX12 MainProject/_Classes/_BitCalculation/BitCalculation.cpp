#include "BitCalculation.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/_Object/ObjectBase.h"

/**
* @brief �r�b�g�����炷
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
	const float _sx = 1280.0f / _CN;
	const float _sy = 720.0f / _CN;

	//�i�q�̍��W
	const int _kx = (int)(pos.x / _sx);
	const int _ky = (int)(pos.y / _sy);

	//bit����
	const int _bx = BitSlide(_kx);
	const int _by = BitSlide(_ky);

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
	// ����A�E���̍��W
	//DirectX::XMFLOAT2 _UL = DirectX::XMFLOAT2(m_pos.x - radian, m_pos.y + radian);
	//DirectX::XMFLOAT2 _UR = DirectX::XMFLOAT2(m_pos.x + radian, m_pos.y - radian);
	DirectX::XMFLOAT2 _UL = DirectX::XMFLOAT2(m_pos.x, m_pos.y);
	DirectX::XMFLOAT2 _UR = DirectX::XMFLOAT2(m_pos.x, m_pos.y);

	// ���ꂼ��̃��[�g������
	int _mUL = PointToMorton(_UL);
	int _mUR = PointToMorton(_UR);

	const int _XOR = _mUL ^ _mUR;

	int _k = 0;
	// XOR��00���o�Ă���܂Ń��[�v���āA���̉��������K�ɕۑ�����
	for (int _b = _XOR; _b != 0; _b >>= 2, _k++);

	numbers.Level_		= DivisionLevel - _k;
	numbers.LsIndex_	= _mUR >> (2 * _k);
	numbers.MsIndex_	= GetIndex(numbers.Level_, numbers.LsIndex_);
}