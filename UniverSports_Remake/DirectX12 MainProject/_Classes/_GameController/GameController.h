#pragma once

#include "_Classes/_UI/_OriTimer/OriTimer.h"

class GameController {
public:
	GameController();
	virtual ~GameController();

	void Update(const float deltaTime);
	bool GameFined();

private:
	const float TIME_COUNT = 3.0f;
	const float TIME_LIMIT[4] = { TIME_COUNT,TIME_COUNT,0.0f + TIME_COUNT,0.0f };
	OriTimer* timer_;
};