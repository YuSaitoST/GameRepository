#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#define Light MainLight::GetInstance()

class MainLight {
public:
	MainLight();
	virtual ~MainLight() = default;

	static MainLight& GetInstance() {
		static MainLight _light;
		return _light;
	}

	void Initialize();
	void Set();
	void Enable();

private:
	D3DLIGHT9 light_;
};