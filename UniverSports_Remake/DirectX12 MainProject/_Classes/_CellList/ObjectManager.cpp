#include "ObjectManager.h"

ObjPlayer* ObjectManager::obj_player_[2];
ObjBall* ObjectManager::obj_ball_[1];
ObjectBase* ObjectManager::obj_wire_[4];

ObjectManager::ObjectManager() {
	obj_player_[0] = new ObjPlayer(OPERATE_TYPE::MANUAL, POS_START[0], 1.0f);
	obj_player_[1] = new ObjPlayer(OPERATE_TYPE::COMPUTER, POS_START[1], 1.0f);

	obj_ball_[0] = new ObjBall(Vector3(99.0f, 99.0f, 0.0f), 1.0f);
}

ObjectManager::~ObjectManager() {
	for (int _i = N_BALL - 1; 0 <= _i; _i--)
		delete obj_ball_[_i];
	
	for (int _i = N_PLAYER - 1; 0 <= _i; _i--)
		delete obj_player_[_i];
}

void ObjectManager::Initialize() {
	for (int _i = 0; _i < N_PLAYER; _i++)
		obj_player_[_i]->Initialize(_i);

	for (int _i = 0; _i < N_BALL; _i++)
		obj_ball_[_i]->Initialize(_i);
}

void ObjectManager::LoadAssets() {
	mod_ball_ = DX9::Model::CreateFromFile(DXTK->Device9, L"_Models\\_Ball\\ball.X");
	mod_ball_->SetScale(GAME_CONST.BA_SCALE);
	mod_ball_->SetMaterial(ObjectBase::GetNomMaterial());

	for (int _i = 0; _i < N_PLAYER; _i++)
		obj_player_[_i]->LoadAssets(PLAYER_FILENAME[_i]);

	for (ObjectBase* obj : obj_ball_)
		obj->LoadAssets(mod_ball_);
}

void ObjectManager::Update(const float deltaTime) {
	for (ObjectBase* obj : obj_player_)
		obj->Update(deltaTime);

	for (ObjectBase* obj : obj_ball_)
		obj->Update(deltaTime);
}

void ObjectManager::RenderModels() {
	for (ObjectBase* obj : obj_player_)
		obj->Render();

	for (ObjectBase* obj : obj_ball_)
		obj->Render(mod_ball_);
}

void ObjectManager::RenderSprites() {
	for (ObjectBase* obj : obj_player_)
		obj->UIRender();
}

void ObjectManager::AddWorld(btDynamicsWorld* physics_world_) {
	for (ObjectBase* obj : obj_player_)
		physics_world_->addRigidBody(obj->myRigidbody());

	physics_world_->addRigidBody(obj_ball_[0]->myRigidbody());
}

void ObjectManager::RemoveWorld(btDynamicsWorld* physics_world_) {
	for (int _i = 1; 0 <= _i; _i--)
		physics_world_->removeRigidBody(obj_player_[_i]->myRigidbody());
}

Vector2 ObjectManager::PlayerHandsPos(int index) {
	return obj_player_[index]->Get_HandPos();
}

Vector2 ObjectManager::TheClosestPos(ObjectBase* targetObj, Vector2 pos) {
	//const int _size = sizeof(targetObj) / sizeof(ObjectBase);
	Vector2 _position = Vector2(99.0f, 99.0f);  // 一番近い座標
	//Vector2 _target;  // 現在調べている座標
	//float _new_comparison;  // 現在調べている距離
	//float _min_comparison = 99.0f;  // 一番近い距離

	//for (int _i = 0; _i < _size;_i++) {
	//	if ((targetObj[_i].myPosition().x == pos.x) && (targetObj[_i].myPosition().y == pos.y))
	//		continue;

	//	_target = targetObj[_i].myPosition();
	//	_new_comparison = std::sqrtf(
	//		std::powf(pos.x - _target.x, 2) +
	//		std::powf(pos.y - _target.y, 2)
	//	);

	//	if (_new_comparison < _min_comparison) {
	//		_min_comparison = _new_comparison;
	//		_position = _target;
	//	}
	//}

	return _position;
}

Vector2 ObjectManager::TheClosestPlayerPos(Vector2 pos) {
	//auto dpoin = &obj_player_;
	//auto base = (ObjectBase*)dpoin;
	//return TheClosestPos(*(*dpoin), pos);
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
	Vector2 _position = Vector2(99.0f, 99.0f);  // 一番近い座標
	Vector2 _target;  // 現在調べている座標
	float _new_comparison;  // 現在調べている距離
	float _min_comparison = 99.0f;  // 一番近い距離

	for (ObjectBase* obj : obj_ball_) {
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