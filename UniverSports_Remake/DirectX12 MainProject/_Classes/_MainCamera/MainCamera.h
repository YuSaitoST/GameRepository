#pragma once

#include"Base/pch.h"
#include"Base/dxtk.h"

#define Camera MainCamera::GetInstance()

using namespace DirectX;

class MainCamera {
public:
	MainCamera();
	virtual ~MainCamera() = default;

	static MainCamera& GetInstance() {
		static MainCamera _inctance;
		return _inctance;
	}

	void Initialize();
	void Render();

	DX9::CAMERA GetCamera() const { return camera_; };

private:
	DX9::CAMERA camera_;
	SimpleMath::Vector3 pos_;
};