#include "BitCalculation.h"

int BitCalculation::BitSlide(int b) {
	b = (b | b << 2) & 0x33;
	b = (b | b << 1) & 0x55;
	return b;
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