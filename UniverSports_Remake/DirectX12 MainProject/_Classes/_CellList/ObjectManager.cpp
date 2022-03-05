#include "ObjectManager.h"

ObjectBase* ObjectManager::obj_player_[2];

ObjectManager::ObjectManager() {
	obj_player_[0] = new ObjPlayer(OPERATE_TYPE::MANUAL, POS_START[0], 1.0f);
	obj_player_[1] = new ObjPlayer(OPERATE_TYPE::COMPUTER, POS_START[1], 1.0f);
}

ObjectManager::~ObjectManager() {
	delete obj_player_[1];
	delete obj_player_[0];
}

void ObjectManager::Initialize() {
	for (int _i = 0; _i < 2; _i++)
		obj_player_[_i]->Initialize(_i);
}

void ObjectManager::LoadAssets() {
	for (int _i = 0; _i < 2; _i++)
		obj_player_[_i]->LoadAssets(PLAYER_FILENAME[_i]);
}

void ObjectManager::Update(const float deltaTime) {
	for (ObjectBase* obj : obj_player_)
		obj->Update(deltaTime);
}

void ObjectManager::RenderModels() {
	for (ObjectBase* obj : obj_player_)
		obj->Render();
}

void ObjectManager::RenderSprites() {
	for (ObjectBase* obj : obj_player_)
		obj->UIRender();
}

void ObjectManager::AddWorld(btDynamicsWorld* physics_world_) {
	for (ObjectBase* obj : obj_player_)
		physics_world_->addRigidBody(obj->myRigidbody());
}

void ObjectManager::RemoveWorld(btDynamicsWorld* physics_world_) {
	for (int _i = 1; 0 <= _i; _i--)
		physics_world_->removeRigidBody(obj_player_[_i]->myRigidbody());
}

Vector2 ObjectManager::TheClosestPlayerPos(Vector2 pos) {
	Vector2 _position = Vector2(99.0f, 99.0f);  // 一番近い座標
	Vector2 _target;  // 現在調べている座標
	float _new_comparison;  // 現在調べている距離
	float _min_comparison = 99.0f;  // 一番近い距離

	for (ObjectBase* obj : obj_player_) {
		if ((obj->myPosition().x == pos.x) && (obj->myPosition().y == pos.y))
			continue;

		_target = obj->myPosition();
		_new_comparison = std::sqrtf(
			std::powf(pos.x - _target.x, 2) + 
			std::powf(pos.y - _target.y, 2)
		);

		if (_new_comparison < _min_comparison) {
			_min_comparison = _new_comparison;
			_position = _target;
		}
	}

	return _position;
}

// まだボールは実装していないため、ベースだけ残しておく
Vector2 ObjectManager::TheClosestBallPos(Vector2 pos) {
	return Vector2::Zero;
}