#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX::SimpleMath;

class BitCalculation {
public:
	BitCalculation() {}
	virtual ~BitCalculation() {}

	static int BitSlide(int bit);
	static int PointToMorton(Vector2 pos);
	static int GetIndex(int Level, int Index);  // L,IÇ©ÇÁMÇãÅÇﬂÇÈ

	static const int N_ = 2;
};