#include "GameController.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_AtEndCondition/AECDodgeBallNomal.h"
#include "_AtEndCondition/AECDodgeBall2on2.h"
#include <cassert>

bool GameController::gameStart_ = false;

GameController::GameController() {
	startTime_	= TIME_LIMIT[(int)DontDestroy->GameMode_.SelectionMode()] + TIME_COUNT;
	timer_		= std::make_unique<CountTimer>(startTime_);
	countDown_	= std::make_unique<CountDownUI>();
	blackOut_	= std::make_unique<BlackOut>();
	ui_finish_	= std::make_unique<Finish>();
	se_whistle_ = std::make_unique<SoundPlayer>();

	GameModes gameMode = DontDestroy->GameMode_;
	if (gameMode.isDODGEBALL_NOMAL())
		atEndCondition_ = std::make_unique<AECDodgeBallNomal>();
	else if (gameMode.isDODGEBALL_2ON2())
		atEndCondition_ = std::make_unique<AECDodgeBall2on2>();
	else
		assert(!"不正なゲームモードです");
}

void GameController::Initialize() {
	countDown_->Initialize();
	blackOut_->Initialize(BLACKOUT_MODE::FADE_OUT);
	ui_finish_->Initialize();
	se_whistle_->Initialize(USFN_SOUND::SE::WHISTLE, SOUND_TYPE::SE, 1.0f);
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
	return atEndCondition_->IsFined();

	assert(!"不正なゲームモードです__in GameController::GameFined()");
	return false;
}