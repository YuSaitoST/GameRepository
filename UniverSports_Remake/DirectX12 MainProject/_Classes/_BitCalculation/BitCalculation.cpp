#include "BitCalculation.h"
#include "_Classes/_Field/Field.h"
#include "_Classes/_CellList/_Object/ObjectBase.h"

/**
* @brief ビットをずらす
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
	//格子の1辺における分割数
	const int _CN = (int)std::pow(2, BitCalculation::DivisionLevel);

	//格子の一辺の長さ
	const float _sx = 1280.0f / _CN;
	const float _sy = 720.0f / _CN;

	//格子の座標
	const int _kx = (int)(pos.x / _sx);
	const int _ky = (int)(pos.y / _sy);

	//bit操作
	const int _bx = BitSlide(_kx);
	const int _by = BitSlide(_ky);

	//OR演算して返す
	return (_bx | (_by << 1));
}

/**
* @brief 空間レベルとレベル毎のインデックスからモートン符号を求める
* @param Level 空間レベル
* @param Index レベル毎のインデックス
* @return モートン符号
*/
int BitCalculation::GetIndex(int Level, int Index) {
	return (((std::pow(NumberOfDivisions, Level) - 1) / (NumberOfDivisions - 1)) + Index);  //等比級数
}

/**
* @brief 受け取った情報から所属する空間を求める
* @param m_pos 座標
* @param radian 物体の半径
* @param numbers 空間番号セット
*/
void BitCalculation::MoverToMorton(DirectX::XMFLOAT2 m_pos, float radian, SpaceNumber& numbers) {
	// 左上、右下の座標
	//DirectX::XMFLOAT2 _UL = DirectX::XMFLOAT2(m_pos.x - radian, m_pos.y + radian);
	//DirectX::XMFLOAT2 _UR = DirectX::XMFLOAT2(m_pos.x + radian, m_pos.y - radian);
	DirectX::XMFLOAT2 _UL = DirectX::XMFLOAT2(m_pos.x, m_pos.y);
	DirectX::XMFLOAT2 _UR = DirectX::XMFLOAT2(m_pos.x, m_pos.y);

	// それぞれのモートンを代入
	int _mUL = PointToMorton(_UL);
	int _mUR = PointToMorton(_UR);

	const int _XOR = _mUL ^ _mUR;

	int _k = 0;
	// XORを00が出てくるまでループして、その回った数をKに保存する
	for (int _b = _XOR; _b != 0; _b >>= 2, _k++);

	numbers.Level_		= DivisionLevel - _k;
	numbers.LsIndex_	= _mUR >> (2 * _k);
	numbers.MsIndex_	= GetIndex(numbers.Level_, numbers.LsIndex_);
}