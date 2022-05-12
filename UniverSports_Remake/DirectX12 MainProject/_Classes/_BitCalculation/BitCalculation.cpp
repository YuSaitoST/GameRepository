#include "BitCalculation.h"

int BitCalculation::BitSlide(int bit) {
	bit = (bit | bit << 2) & 0x33;
	bit = (bit | bit << 1) & 0x55;
	return bit;
}

int BitCalculation::PointToMorton(Vector2 pos) {
	// ŠiŽq‚Ì1•Ó‚É‚¨‚¯‚é•ªŠ„”
	const int _CN = (int)std::pow(2, N_);

	// ŠiŽq‚Ìˆê•Ó‚Ì’·‚³
	const float _sx = 1280.0f / _CN;
	const float _sy = 720.0f / _CN;

	// ŠiŽq‚ÌÀ•W
	const int _kx = (int)(pos.x / _sx);
	const int _ky = (int)(pos.y / _sy);

	// bit‘€ì
	const int _bx = BitSlide(_kx);
	const int _by = BitSlide(_ky);

	// OR‰‰ŽZ‚µ‚Ä•Ô‚·
	return (_bx | (_by << 1));
}

// Level,Index‚©‚çMortonIndex‚ð‹‚ß‚é
int BitCalculation::GetIndex(int Level, int Index) {
	const int _CR = (int)std::pow(4, Level);  // Common ratio (Œö”ä)
	return (((_CR - 1) / (4 - 1)) + Index);  // “™”ä‹‰”
}