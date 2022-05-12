#include "BitCalculation.h"

int BitCalculation::BitSlide(int bit) {
	bit = (bit | bit << 2) & 0x33;
	bit = (bit | bit << 1) & 0x55;
	return bit;
}

int BitCalculation::PointToMorton(Vector2 pos) {
	// �i�q��1�ӂɂ����镪����
	const int _CN = (int)std::pow(2, N_);

	// �i�q�̈�ӂ̒���
	const float _sx = 1280.0f / _CN;
	const float _sy = 720.0f / _CN;

	// �i�q�̍��W
	const int _kx = (int)(pos.x / _sx);
	const int _ky = (int)(pos.y / _sy);

	// bit����
	const int _bx = BitSlide(_kx);
	const int _by = BitSlide(_ky);

	// OR���Z���ĕԂ�
	return (_bx | (_by << 1));
}

// Level,Index����MortonIndex�����߂�
int BitCalculation::GetIndex(int Level, int Index) {
	const int _CR = (int)std::pow(4, Level);  // Common ratio (����)
	return (((_CR - 1) / (4 - 1)) + Index);  // ���䋉��
}