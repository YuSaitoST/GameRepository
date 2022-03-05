#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX::SimpleMath;

class InputBase {
public:
	virtual void Initialize() = 0;
	virtual void Accepts() = 0;
	virtual void ResetMember() = 0;
};