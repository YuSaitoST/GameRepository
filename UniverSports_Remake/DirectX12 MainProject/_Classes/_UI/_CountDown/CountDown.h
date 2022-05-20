#pragma once

#include"Base/pch.h"
#include"Base/dxtk.h"
#include"_Classes/_SoundPlayer/SoundPlayer.h"

class CountDownUI {
public:
	CountDownUI();
	virtual ~CountDownUI();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, float nowCount);
	void Render(float count) const;

private:
	const float			CENTER_X = 88.0f;
	const float			CENTER_Y = 37.5f;
	const float			POS_X	 = 543.0f + CENTER_X;
	const float			POS_Y	 = 325.0f + CENTER_Y;

	SoundPlayer*		se_count_;
	DX9::SPRITE			sprite_[4];
	float				alpha_;
	float				scale_;
	bool				se_played_;
};