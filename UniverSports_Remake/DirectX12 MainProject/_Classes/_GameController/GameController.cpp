#include "GameController.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_ControllerState/StartState.h"
#include "_ControllerState/PlayState.h"
#include "_ControllerState/FinishState.h"
#include "_AtEndCondition/AECDodgeBallNomal.h"
#include "_AtEndCondition/AECDodgeBall2on2.h"
#include "_AtEndCondition/AECHandBall.h"
#include <cassert>

bool GameController::gamePlay_ = false;

GameController::GameController() {
	progress_	= std::make_unique<StartState>();
	
	progressList_.reserve(2);
	progressList_.push_back(std::make_unique<PlayState>());
	progressList_.push_back(std::make_unique<FinishState>());

	GameModes gameMode = DontDestroy->GameMode_;
	if (gameMode.isDODGEBALL_NOMAL())
		atEndCondition_ = std::make_unique<AECDodgeBallNomal>();
	else if (gameMode.isDODGEBALL_2ON2())
		atEndCondition_ = std::make_unique<AECDodgeBall2on2>();
	else if (gameMode.isHANDBALL())
		atEndCondition_ = std::make_unique<AECHandBall>();
	else
		assert(!"不正なゲームモードです");
}

void GameController::Initialize() {
	progress_->Initialize();
	progressList_[0]->Initialize();
	progressList_[1]->Initialize();

	gamePlay_ = false;
}

void GameController::LoadAssets() {
	progress_->LoadAsstes();
	progressList_[0]->LoadAsstes();
	progressList_[1]->LoadAsstes();
}

NextScene GameController::Update(const float deltaTime) {
	progress_->Update(deltaTime);

	if (progress_->ChangeDrawing(this)) {
		if (progressList_.size() == 0) {
			return NextScene::ResultScene;
		}

		progress_.reset(progressList_.front().release());
		progressList_.erase(progressList_.begin() + 0);
	}

	return NextScene::Continue;
}

void GameController::Render() {
	progress_->Render();
}

/**
* @brief ゲームの終了状態を返す
* @return ゲームの終了状態
*/
bool GameController::GameFined() {
	return atEndCondition_->IsFined(progress_->GetTimer());
}