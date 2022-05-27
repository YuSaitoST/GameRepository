/**
 * @file GameController.h
 * @brief ゲームの進行管理クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Scene.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"
#include "_Classes/_UI/_CountDown/CountDown.h"
#include "_Classes/_UI/_BlackOut/BlackOut.h"
#include "_Classes/_UI/_Finish/Finish.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"

class GameController {
public:
	GameController();
	virtual ~GameController() {}

	GameController(GameController const&) = delete;
	GameController& operator= (GameController const&) = delete;

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
	const float	SPEED_FADE[3]	= { 51.0f, 510.0f, 0.0f };

	//! タイマー
	std::unique_ptr<CountTimer> timer_;

	//! 開始前カウントダウン
	std::unique_ptr<CountDownUI> countDown_;

	//! ブラックアウト
	std::unique_ptr<BlackOut> blackOut_;

	//! 終了時テキスト
	std::unique_ptr<Finish> ui_finish_;

	//! 終了時SE
	std::unique_ptr<SoundPlayer> se_whistle_;

	//! ゲームの制限時間
	float			startTime_;

	//! ゲームの進行状態フラグ
	static bool		gameStart_;
};