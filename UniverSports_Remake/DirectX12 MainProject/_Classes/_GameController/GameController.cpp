#include "GameController.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include <cassert>

bool GameController::gameStart_ = false;

GameController::GameController() {
	startTime_	= TIME_LIMIT[(int)DontDestroy->GameMode_.SelectionMode()] + TIME_COUNT;
	timer_		= std::make_unique<CountTimer>(startTime_);
	countDown_	= std::make_unique<CountDownUI>();
	blackOut_	= std::make_unique<BlackOut>();
	ui_finish_	= std::make_unique<Finish>();
	se_whistle_ = std::make_unique<SoundPlayer>();
}

void GameController::Initialize() {
	countDown_->Initialize();
	blackOut_->Initialize(BLACKOUT_MODE::FADE_OUT);
	ui_finish_->Initialize();
	se_whistle_->Initialize(L"_Sounds\\_SE\\_Main\\se_whistle.wav", SOUND_TYPE::SE, 1.0f);
	gameStart_ = false;
}

void GameController::LoadAssets() {
	countDown_->LoadAssets();
	blackOut_->LoadAsset();
	ui_finish_->LoadAssets();
}

NextScene GameController::Update(const float deltaTime) {
	timer_->Update(deltaTime);
	blackOut_->Update(SPEED_FADE[blackOut_->GetMode()] * deltaTime);
	countDown_->Update(deltaTime, (TIME_COUNT - (startTime_ - timer_->NowTime())));

	if (GameFined()) {
		if (gameStart_)
			blackOut_->ChangeMode(BLACKOUT_MODE::FADE_IN);

		gameStart_ = false;
		ui_finish_->Update(deltaTime);

		const bool _seFined = se_whistle_->PlayOneShot(deltaTime);

		//全てのアニメーションが終了したらリザルトへ遷移する
		if (blackOut_->isDone() && ui_finish_->isAnimationFine() && _seFined)
			return NextScene::ResultScene;
	}
	return NextScene::Continue;
}

void GameController::Render() {
	blackOut_->Render();
	ui_finish_->Render();

	if (gameStart_)
		return;

	countDown_->Render((TIME_COUNT - std::max(0.0f, (startTime_ - timer_->NowTime()))));
	gameStart_ = TIME_COUNT <= (startTime_ - timer_->NowTime());  // カウントダウン(4.2f)より経過時間が長ければtrue
}

/**
* @brief ゲームの終了状態を返す
* @return ゲームの終了状態
*/
bool GameController::GameFined() {
	GameModes _gameMode = DontDestroy->GameMode_;

	if (_gameMode.isHANDBALL())
		return timer_->TimeOut();
	else if (_gameMode.isDODGEBALL_NOMAL())
		return (RemainingNumberOfPlayer() <= 1);
	else if (_gameMode.isDODGEBALL_2ON2())
		return (RemainingOfTeam() <= 1);
	else if (_gameMode.isBILLIARDS())
		return Press.MiniGameFinedKey(0);

	assert(!"不正なゲームモードです__in GameController::GameFined()");
	return false;
}


/**
* @brief 残りの選手が1人かを調べる
* @return 現在残っている人数
*/
int GameController::RemainingNumberOfPlayer() {
	int count = 0;
	count += (int)DontDestroy->Survivor_[0];
	count += (int)DontDestroy->Survivor_[1];
	count += (int)DontDestroy->Survivor_[2];
	count += (int)DontDestroy->Survivor_[3];
	return count;
}

/**
* @brief 残りのチームが1つかを調べる
* @return 現在残っているチーム数
*/
int GameController::RemainingOfTeam() {
	// 残り人数が2人より多いまたは最後の1人なら、調べる必要がないため、早期リターンする
	const int count = RemainingNumberOfPlayer();
	if ((2 < count) || (count == 1))
		return count;

	int index = 0;
	int lastPlayersTeamID[2] = { 0,0 };
	for (int _i = 0; (_i < 4) && (index < 2); ++_i) {
		if (DontDestroy->Survivor_[_i]) {
			lastPlayersTeamID[index] = DontDestroy->TeamID[_i];
			index += 1;
		}
	}
	return (int)(lastPlayersTeamID[0] == lastPlayersTeamID[1]);
}