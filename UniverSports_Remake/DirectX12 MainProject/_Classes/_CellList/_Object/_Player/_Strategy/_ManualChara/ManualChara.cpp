#include "ManualChara.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"

void ManualChara::Initialize(int id, ObjPlayer* player) {
	player_ = player;
	
	for (ActionBase* act : actList_)
		act->Initialize(id);
}

void ManualChara::LoadAssets() {
	for (ActionBase* act : actList_)
		act->LoadAssets();
}

void ManualChara::Update(const float deltaTime) {
	for (int _i = 0; _i < actList_.size(); _i++)
		actList_[_i]->Update(deltaTime, Press.MoveDirection(player_->myObjectID()), *player_);
	
	rotate_x_ = SeekRotateX(deltaTime, Press.MoveDirection(player_->myObjectID()));
}