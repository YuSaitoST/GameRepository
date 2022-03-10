#include "ComputerChara.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"

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
	// [‚³—Dæ’Tõi‚Ì‚Â‚à‚è‚¾‚Á‚½j
	for (int _i = 0; _i < actList_.size(); _i++)
		if (actList_[_i]->Think(*player_))
			actList_[_i]->Update(deltaTime, *player_);

	SeekRotateX(deltaTime, player_->myObjectID());
}

void ComputerChara::SeekRotateX(const float deltaTime, int index) {
	const SimpleMath::Vector2 _pad = actList_[0]->GetDirection();

	direction_.x = _pad.x * std::sqrtf(1.0f - 0.5f * _pad.x * _pad.y);
	direction_.y = _pad.y * std::sqrtf(1.0f - 0.5f * _pad.x * _pad.y);
	direction_.z = 0;

	prevForward_ = SimpleMath::Vector3::Lerp(prevForward_, direction_, deltaTime * 1.0f);
	rotate_x_ = atan2f(prevForward_.y, prevForward_.x);
}
