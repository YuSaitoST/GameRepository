#include "ActThrasher.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_CellList/ObjectManager.h"

ActThrasher::ActThrasher() {
	effect_ = new EffThrasher();
	gauge_ = new Gauge();
}

ActThrasher::~ActThrasher() {
	delete gauge_;
	delete effect_;
}

void ActThrasher::Initialize(int id) {
	effect_->Initialize("Thruster" + std::to_string(id));
	gauge_->Initialize();
}

void ActThrasher::LoadAssets() {
	effect_->LoadAsset(L"_Effects\\_Thruster\\Thruster_001\\Thruster.efk");
	gauge_->LoadAssets();
}

void ActThrasher::Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player) {
	const Vector2 _pos = player.myPosition();
	const bool _isUsed = Press.ThrasherKey(player.myObjectID());

	gauge_->SetPosition(Vector3(_pos.x, _pos.y, 0.0f));
	gauge_->Update(deltaTime, effect_->usedThrasher_);

	effect_->usedThrasher_ = _isUsed && (0.1f < gauge_->GetProportion());
	effect_->Update(deltaTime, player.myRotate().x, Vector3(_pos.x, _pos.y, 0.0f), Vector3(direction.x, direction.y, 0.0f));
}

void ActThrasher::Update(const float deltaTime, ObjPlayer& player) {
	const Vector2 _pos = player.myPosition();
	effect_->Update(deltaTime, player.myRotate().x, Vector3(_pos.x, _pos.y, 0.0f), Vector3(direction_.x, direction_.y, 0.0f));
}

void ActThrasher::UIRender() {
	gauge_->Render();
}

bool ActThrasher::Think(ObjPlayer& my) {
	// 他のObjectBaseクラスを参照できるようにしたい

	// これを利用して、加速するかを検討する...かな?
	const SimpleMath::Vector2 _closestPlayerPos = ObjectManager::TheClosestPlayerPos(my.myPosition());
	direction_ = _closestPlayerPos - my.myPosition();
	direction_.Normalize();

	return true;
}