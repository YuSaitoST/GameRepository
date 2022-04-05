#include "GameController.h"
#include "DontDestroyOnLoad.h"
#include <cassert>

GameController::GameController() {
	startTime_	= TIME_LIMIT[DontDestroy->GameMode_] + TIME_COUNT;
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

	if (timer_->NowTime() < TIME_LIMIT[DontDestroy->GameMode_])
		return;

	countDown_->Render((TIME_COUNT - std::max(0.0f, (startTime_ - timer_->NowTime()))));
}

bool GameController::GameFined() {
	if (DontDestroy->isHANDBALL())
		return timer_->TimeOut();
	else if (DontDestroy->isDODGEBALL())
		return (DontDestroy->Survivor_ == 1);

	assert(!"�s���ȃQ�[�����[�h�ł�__in GameController::GameFined()");
	return false;
}