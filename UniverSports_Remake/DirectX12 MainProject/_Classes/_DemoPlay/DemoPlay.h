#pragma once

#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_MoviePlayer/MoviePlayer.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

class DemoPlay {
public:
	DemoPlay(float playBack);
	virtual ~DemoPlay();

	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

	void ResetTime() { timer_->ResetCountTime(); };
	bool IsDisplay() const { return isDisplay_; };

private:
	MoviePlayer* mv_demo_;
	CountTimer* timer_;
	bool isDisplay_;
};