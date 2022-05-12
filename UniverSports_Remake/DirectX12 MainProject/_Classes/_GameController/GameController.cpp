#include "GameController.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include <cassert>

bool GameController::gameStart_;

GameController::GameController() {
	startTime_	= TIME_LIMIT[(int)DontDestroy->GameMode_.SelectionMode()] + TIME_COUNT;
	timer_		= new OriTimer(startTime_);
	countDown_	= new CountDownUI();
	blackOut_	= new BlackOut();
	ui_finish_	= new Finish();
	se_whistle_ = new SoundPlayer();
}

GameController::~GameController() {
	delete se_whistle_;
	delete ui_finish_;
	delete blackOut_;
	delete countDown_;
	delete timer_;
}

void GameController::Initialize() {
	countDown_->Initialize();
	blackOut_->Initialize(BLACKOUT_MODE::FADE_IN);
	ui_finish_->Initialize();
	se_whistle_->Initialize(L"_Sounds\\_SE\\_Main\\se_whistle.wav", SOUND_TYPE::SE, 1);
	se_whistle_->AutoPlay(true);
}

void GameController::LoadAssets() {
	countDown_->LoadAssets();
	blackOut_->LoadAsset();
	ui_finish_->LoadAssets();
}

NextScene GameController::Update(const float deltaTime) {
	timer_->Update(deltaTime);
	countDown_->Update(deltaTime, (TIME_COUNT - std::max(0.0f, (startTime_ - timer_->NowTime()))));

	if (GameFined()) {
		gameStart_ = false;
		blackOut_->Update(deltaTime);
		ui_finish_->Update(deltaTime);
		se_whistle_->Update(deltaTime);

		if (blackOut_->isDone() && ui_finish_->isAnimationFine() && se_whistle_->isFined())
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
	gameStart_ = TIME_COUNT <= (startTime_ - timer_->NowTime());  // カウントダウン(4.2f)より経過時間が長ければ
}

bool GameController::GameFined() {
	GameModes _gameMode = DontDestroy->GameMode_;

	if (_gameMode.isHANDBALL())
		return timer_->TimeOut();
	else if (_gameMode.isDODGEBALL_NOMAL())
		return (RemainingNumberOfPlayer() <= 1);
	else if (_gameMode.isDODGEBALL_2ON2())
		return (RemainingOfTeam() <= 1);
	else if (_gameMode.isBILLIARDS())
		return Press.MinGameFinedKey(0);

	assert(!"不正なゲームモードです__in GameController::GameFined()");
	return false;
}

int GameController::RemainingNumberOfPlayer() {
	int count = 0;
	count += (int)DontDestroy->Survivor_[0];
	count += (int)DontDestroy->Survivor_[1];
	count += (int)DontDestroy->Survivor_[2];
	count += (int)DontDestroy->Survivor_[3];
	return count;
}

int GameController::RemainingOfTeam() {
	// 残り人数が2人より多いまたは最後の1人なら、調べる必要がないため、早期リターンする
	const int count = RemainingNumberOfPlayer();
	if ((2 < count) || (count == 1))
		return count;

	int index = 0;
	int lastPlayersTeamID[2];
	for (int _i = 0; (_i < 4) && (index < 2); ++_i) {
		if (DontDestroy->Survivor_[_i]) {
			lastPlayersTeamID[index] = DontDestroy->TeamID[_i];
			index += 1;
		}
	}
	return (int)(lastPlayersTeamID[0] == lastPlayersTeamID[1]);
}