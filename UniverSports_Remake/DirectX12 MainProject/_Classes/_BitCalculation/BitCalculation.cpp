#include "BitCalculation.h"

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