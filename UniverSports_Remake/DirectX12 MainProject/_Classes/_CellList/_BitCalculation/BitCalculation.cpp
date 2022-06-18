#include "BitCalculation.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/_Object/ObjectBase.h"

/**
* @brief ビットを1つずつずらす
* @param bit 格子の座標
* @return 変換したビット値
*/
int BitCalculation::BitSlide(int bit) {
	bit = (bit | bit << 2) & 0x33;
	bit = (bit | bit << 1) & 0x55;
	return bit;
}

/**
* @brief 受け取った座標からモートン符号を求める
* @param pos 座標
* @return モートン符号
*/
int BitCalculation::PointToMorton(DirectX::XMFLOAT2 pos) {
	//格子の一辺の長さ
	const float _sx = (int)FIELD::SIZE_X >> BitCalculation::DivisionLevel;
	const float _sy = (int)FIELD::SIZE_Y >> BitCalculation::DivisionLevel;

	//格子の座標
	const int _kx = (int)(std::min((pos.x + FIELD::HALF_X), FIELD::SIZE_X) / _sx);
	const int _ky = (int)(std::min((pos.y + FIELD::HALF_Y), FIELD::SIZE_Y) / _sy);

	//右端をエリア内にする
	const int _downBit = ~(1 << 2);
	const int _norx = _kx & _downBit;
	const int _nory = _ky & _downBit;

	//OR演算して返す
	return (BitSlide(_norx) | (BitSlide(_nory) << 1));
}

/**
* @brief 受け取った情報から所属する空間を求める
* @param m_pos 座標
* @param radian 物体の半径
* @param numbers 空間番号セット
*/
void BitCalculation::MoverToMorton(DirectX::XMFLOAT2 m_pos, float radian, SpaceNumber& numbers) {
	//左上、右下の座標
	const DirectX::XMFLOAT2 _UL = DirectX::XMFLOAT2(m_pos.x - radian, m_pos.y + radian);
	const DirectX::XMFLOAT2 _UR = DirectX::XMFLOAT2(m_pos.x + radian, m_pos.y - radian);

	//それぞれのモートンを代入
	const int _mUL = PointToMorton(_UL);
	const int _mUR = PointToMorton(_UR);

	//XORを00が出てくるまでループして、その回った数をKに保存する
	int _k = 0;
	for (int _XOR = _mUL ^ _mUR; _XOR != 0; _XOR >>= 2, _k++);

	//各値の算出
	numbers.Level_		= DivisionLevel - _k;
	numbers.LsIndex_	= _mUR >> (2 * _k);
	numbers.MsIndex_	= GetIndex(numbers.Level_, numbers.LsIndex_);
}