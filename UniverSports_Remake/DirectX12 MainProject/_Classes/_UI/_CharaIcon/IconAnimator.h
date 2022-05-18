#pragma once

#include "CharaIcon.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

class IconAnimator {
public:
	IconAnimator();
	virtual ~IconAnimator();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render(const int lifeCount, int index);

	static void DisplayOn() { display_ = true; }

private:
	CharaIcon* icon_[4];
	CountTimer* display_time_;
	float alpha_;
	static bool display_;

	const float SPEED_FADEIN	= 255.0f;
	const float SPEED_FADEOUT	= 127.5f;

	const int WIDTH				= 50;
	const int CEN_X_1			= 1280 * 0.5f - WIDTH - 40 * 3;
	const int CEN_X_2			= 1280 * 0.5f + WIDTH;
	const int CEN_Y_1			= 20;
	const int CEN_Y_2			= CEN_Y_1 + 40 + 10;

	const SimpleMath::Vector3 POS_LEFTICON[4] = {
		SimpleMath::Vector3(CEN_X_1,CEN_Y_1,0.0f),
		SimpleMath::Vector3(CEN_X_2,CEN_Y_1,0.0f),
		SimpleMath::Vector3(CEN_X_1,CEN_Y_2,0.0f),
		SimpleMath::Vector3(CEN_X_2,CEN_Y_2,0.0f)
	};
};