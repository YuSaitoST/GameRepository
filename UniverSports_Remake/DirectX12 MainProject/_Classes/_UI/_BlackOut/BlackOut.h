#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

using namespace DirectX;

enum BLACKOUT_MODE {
	FADE_IN,
	FADE_OUT,
	NONE_ANIMATION
};

class BlackOut {
public:
	BlackOut();
	virtual ~BlackOut() = default;

	void Initialize(BLACKOUT_MODE state);
	void LoadAsset();
	void Update(const float deltaTime);
	void Render();

	bool isDone();

private:
	void FadeIn();
	void FadeOut();

private:
	const float		RGBA_MAX		= 255.0f;
	const float		TIME_FADEIN		= 5.0f;
	const float		TIME_FADEOUT	= 0.5f;

private:
	BLACKOUT_MODE	mode_;
	DX9::SPRITE		sprite_;
	float			alpha_;
	float			speed_fadein_;
	float			speed_fadeout_;
	float			time_delta_;
};