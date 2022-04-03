#pragma once

#include "_Classes/_UI/_OriTimer/OriTimer.h"
#include "_Classes/_UI/_CountDown/CountDown.h"

class GameController {
public:
	GameController();
	virtual ~GameController();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();
	bool GameFined();

private:
	const float TIME_COUNT		= 4.2f;
	const float TIME_LIMIT[4]	= { 0.0f, 120.0f, 0.0f, 0.0f };
	OriTimer* timer_;
	CountDownUI* countDown_;

	float startTime_;
};