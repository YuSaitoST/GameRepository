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

	SeekRotate(deltaTime, player_->myObjectID());
}

void ManualChara::SeekRotate(const float deltaTime, int index) {
	const SimpleMath::Vector2 _pad = Press.MoveDirection(index);

	direction_.x = _pad.x * std::sqrtf(1.0f - 0.5f * _pad.x * _pad.y);
	direction_.y = _pad.y * std::sqrtf(1.0f - 0.5f * _pad.x * _pad.y);
	direction_.z = 0;

	prevForward_ = Vector3::Lerp(prevForward_, direction_, deltaTime * 1.0f);
	rotate_x_ = atan2f(prevForward_.y, prevForward_.x);

	forward_ = (prevForward_ != SimpleMath::Vector3::Zero) ? SimpleMath::Vector2(prevForward_.x, prevForward_.y) : forward_;
	//forward_ = SimpleMath::Vector2(prevForward_.x, prevForward_.y);
}