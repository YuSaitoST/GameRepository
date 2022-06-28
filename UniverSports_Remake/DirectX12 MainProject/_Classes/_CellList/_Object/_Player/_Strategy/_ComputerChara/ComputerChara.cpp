#include "ComputerChara.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "DontDestroyOnLoad.h"

void ComputerChara::Initialize(int id, ObjPlayer* player) {
	player_ = player;
	
	for (ActionBase* act : actList_)
		act->Initialize(id);
}

void ComputerChara::LoadAssets() {
	for (ActionBase* act : actList_)
		act->LoadAssets();
}

void ComputerChara::Update(const float deltaTime) {
	//MainSceneˆÈŠO‚È‚çs“®‚µ‚È‚¢
	if (DontDestroy->NowScene_ != NextScene::MainScene)
		return;

	//s“®
	for (ActionBase* act : actList_)
		if (act->Think(*player_))
			act->Update(deltaTime, *player_);

	rotate_x_ = SeekRotateX(deltaTime, actList_[1]->GetDirection());
}