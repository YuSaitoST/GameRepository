#include "ActThrasher.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_CellList/ObjectManager.h"
#include "_Classes/_FileNames/FileNames.h"

ActThrasher::ActThrasher() {
	effect_ = std::make_unique<EffThrasher>();
	gauge_	= std::make_unique<Gauge>();
}

void ActThrasher::Initialize(int id) {
	effect_->Initialize("Thruster" + std::to_string(id));
	gauge_->Initialize();
}

void ActThrasher::LoadAssets() {
	effect_->LoadAsset(USFN_EFF::THRASHER);
	gauge_->LoadAssets();
}

void ActThrasher::Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player) {
	const XMFLOAT2	_pos		= player.myPosition();
	const XMFLOAT2	_forward	= player.myDirection();
	const bool		_isUsed		= Press.ThrasherKey(player.myObjectID());

	gauge_->SetPosition(Vector3(_pos.x, _pos.y, 0.0f));
	gauge_->Update(deltaTime, effect_->usedThrasher_);

	effect_->usedThrasher_		= _isUsed && (0.1f < gauge_->GetProportion());
	effect_->Update(deltaTime, player.myRotate().x, XMFLOAT3(_pos.x, _pos.y, 0.0f), XMFLOAT3(direction.x, direction.y, 0.0f), gauge_->GetProportion());

	player.SetUseThrasher(effect_->usedThrasher_);
}

void ActThrasher::Update(const float deltaTime, ObjPlayer& player) {
	const Vector2 _pos = player.myPosition();

	gauge_->SetPosition(Vector3(_pos.x, _pos.y, 0.0f));
	gauge_->Update(deltaTime, effect_->usedThrasher_);

	effect_->Update(deltaTime, player.myRotate().x, Vector3(_pos.x, _pos.y, 0.0f), Vector3(direction_.x, direction_.y, 0.0f), gauge_->GetProportion());
}

void ActThrasher::UIRender() {
	gauge_->Render();
}

bool ActThrasher::Think(ObjPlayer& my) {
	const ObjectBase* _closestPlayer = my.GetTargetPlayer();
	if (_closestPlayer == nullptr)
		return false;

	direction_ = ((ObjPlayer*)_closestPlayer)->myPosition() - my.myPosition();
	direction_.Normalize();

	return true;
}