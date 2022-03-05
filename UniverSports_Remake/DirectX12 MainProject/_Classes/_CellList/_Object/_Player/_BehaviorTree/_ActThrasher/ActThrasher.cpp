#include "ActThrasher.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_CellList/ObjectManager.h"

ActThrasher::ActThrasher() {
	effect_ = new EffThrasher();
}

ActThrasher::~ActThrasher() {
	delete effect_;
}

void ActThrasher::Initialize(int id) {
	effect_->Initialize("Thruster" + std::to_string(id));
}

void ActThrasher::LoadAssets() {
	effect_->LoadAsset(L"_Effects\\_Thruster\\Thruster_001\\Thruster.efk");
}

void ActThrasher::Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player) {
	const Vector2 _pos = player.myPosition();
	const Vector2 _dir = direction;
	effect_->Update(deltaTime, player.myRotate().x, Vector3(_pos.x, _pos.y, 0.0f), Vector3(_dir.x, _dir.y, 0.0f));
}

void ActThrasher::Update(const float deltaTime, ObjPlayer& player) {
	const Vector2 _pos = player.myPosition();

	effect_->Update(deltaTime, player.myRotate().x, Vector3(_pos.x, _pos.y, 0.0f), Vector3(direction_.x, direction_.y, 0.0f));
}

bool ActThrasher::Think(ObjPlayer& my) {
	// 他のObjectBaseクラスを参照できるようにしたい

	// これを利用して、加速するかを検討する...かな?
	const SimpleMath::Vector2 _closestPlayerPos = ObjectManager::TheClosestPlayerPos(my.myPosition());
	direction_ = _closestPlayerPos - my.myPosition();
	direction_.Normalize();

	return true;
}