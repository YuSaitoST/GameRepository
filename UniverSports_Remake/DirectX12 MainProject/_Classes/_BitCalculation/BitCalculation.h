#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX::SimpleMath;

class BitCalculation {
public:
	BitCalculation() {}
	virtual ~BitCalculation() {}

	static int BitSlide(int b);
	static int PointToMorton(Vector2 pos);

	static const int N_ = 2;
};