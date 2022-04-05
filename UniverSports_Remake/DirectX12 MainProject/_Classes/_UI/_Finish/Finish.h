#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Finish {
public:
	Finish();
	virtual ~Finish() = default;

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

	bool isAnimationFine() const { return (alpha_ == 0.0f); };
	bool isTimeDisplayFine() const { return (time_display_ == 0.0f); };

private:
	const float MOVEMENT = 640.0f;

	DX9::SPRITE sprite_;
	SimpleMath::Vector3 position_;
	float movement_move_;
	float movement_alpha_;
	float time_display_;
	float alpha_;
};