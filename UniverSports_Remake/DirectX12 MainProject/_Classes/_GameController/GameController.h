#pragma once

#include "Scene.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_UI/_OriTimer/OriTimer.h"
#include "_Classes/_UI/_CountDown/CountDown.h"
#include "_Classes/_UI/_BlackOut/BlackOut.h"
#include "_Classes/_UI/_Finish/Finish.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"

class GameController {
public:
	GameController();
	virtual ~GameController();

	void Initialize();
	void LoadAssets();
	NextScene Update(const float deltaTime);
	void Render();
	bool GameFined();

	static bool GamePlay() { return gameStart_; }

private:
	int RemainingNumberOfPlayer();
	int RemainingOfTeam();

	const float TIME_COUNT		= 4.2f;
	const float TIME_LIMIT[4]	= { 0.0f, 0.0f, 120.0f, 0.0f };

	OriTimer*		timer_;
	CountDownUI*	countDown_;
	BlackOut*		blackOut_;
	Finish*			ui_finish_;
	SoundPlayer*	se_whistle_;

	float			startTime_;
	static bool		gameStart_;
};