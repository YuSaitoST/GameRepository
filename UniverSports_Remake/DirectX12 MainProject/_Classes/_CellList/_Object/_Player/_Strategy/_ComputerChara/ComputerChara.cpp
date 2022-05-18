#include "ComputerChara.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "DontDestroyOnLoad.h"

void ComputerChara::Initialize(int id, ObjPlayer* player) {
	player_ = player;
	forward_ = SimpleMath::Vector2::Zero;
	
	for (ActionBase* act : actList_)
		act->Initialize(id);
}

void ComputerChara::LoadAssets() {
	for (ActionBase* act : actList_)
		act->LoadAssets();
}

void ComputerChara::Update(const float deltaTime) {
	//if (DontDestroy->NowScene_ != 3)
	//	return;

	//// [‚³—Dæ’Tõ
	//for (ActionBase* act : actList_)
	//	if (act->Think(*player_))
	//		act->Update(deltaTime, *player_);

	//SeekRotate(deltaTime, player_->myObjectID());
}

void ComputerChara::SeekRotate(const float deltaTime, int index) {
	const SimpleMath::Vector2 _pad = actList_[0]->GetDirection();

	direction_.x = _pad.x * std::sqrtf(1.0f - 0.5f * _pad.x * _pad.y);
	direction_.y = _pad.y * std::sqrtf(1.0f - 0.5f * _pad.x * _pad.y);
	direction_.z = 0;

	prevForward_ = SimpleMath::Vector3::Lerp(prevForward_, direction_, deltaTime * 1.0f);
	rotate_x_ = atan2f(prevForward_.y, prevForward_.x);

	forward_ = (prevForward_ != SimpleMath::Vector3::Zero) ? SimpleMath::Vector2(prevForward_.x, prevForward_.y) : forward_;
}
