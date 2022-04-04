#pragma once

#include"Base/pch.h"
#include"Base/dxtk.h"
#include"_Classes/_SoundPlayer/SoundPlayer.h"

using namespace DirectX;

class CountDownUI {
public:
	CountDownUI();
	virtual ~CountDownUI();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, float nowCount);
	void Render(float count) const;

	void SE_Play();

private:
	const float			POS_X			= 543.0f + 88.0f;
	const float			POS_Y			= 325.0f + 37.5f;
	const std::wstring	FILE_NAME[4]	= {
		L"_Images\\_Main\\_CountDown\\go.png",
		L"_Images\\_Main\\_CountDown\\01.png",
		L"_Images\\_Main\\_CountDown\\02.png",
		L"_Images\\_Main\\_CountDown\\03.png"
	};

	SoundPlayer*		se_count_;
	DX9::SPRITE			sprite_[4];
	float				alpha_;
	float				scale_;
	bool				se_played_;
};