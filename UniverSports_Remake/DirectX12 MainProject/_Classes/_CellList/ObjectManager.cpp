#include "ObjectManager.h"
#include "_Classes/FileNames.h"
#include "DontDestroyOnLoad.h"

ObjPlayer* ObjectManager::obj_player_[N_PLAYER];
std::vector<ObjBall*> ObjectManager::obj_ball_;
//ObjBall* ObjectManager::obj_ball_[5];
ObjWire* ObjectManager::obj_wire_[N_WIRE];

ObjectManager::ObjectManager() {
	DontDestroy->Survivor_[0] = true;
	DontDestroy->Survivor_[1] = true;
	DontDestroy->Survivor_[2] = true;
	DontDestroy->Survivor_[3] = true;

	N_BALL = BALLS[(int)DontDestroy->GameMode_];

	obj_ball_.reserve(N_BALL);

	std::fill(std::begin(DontDestroy->winnerTeamID_), std::end(DontDestroy->winnerTeamID_), -1);

	for (int _i = 0; _i < N_PLAYER; ++_i)
		obj_player_[_i] = new ObjPlayer((OPERATE_TYPE)((int)DontDestroy->charaType_[_i]), POS_START[_i], 1.0f);

	//for (int _i = 0; _i < N_BALL; ++_i)
	//	obj_ball_[_i] = new ObjBall(Vector3(99.0f, 99.0f, 0.0f), 1.0f);
	for (int _i = 0; _i < N_BALL; ++_i)
		obj_ball_.push_back(new ObjBall(Vector3(99.0f, 99.0f, 0.0f), 1.0f));

	for (int _i = 0; _i < N_WIRE; ++_i)
		obj_wire_[_i] = new ObjWire(POS_WIRE[_i], 1.0f);
}

ObjectManager::~ObjectManager() {
	for (int _i = N_WIRE - 1; 0 <= _i; --_i)
		delete obj_wire_[_i];

	//for (int _i = N_BALL - 1; 0 <= _i; --_i)
	//	delete obj_ball_[_i];
	std::vector<ObjBall*> arr(N_BALL);
	obj_ball_.swap(arr);
	
	for (int _i = N_PLAYER - 1; 0 <= _i; --_i)
		delete obj_player_[_i];
}

void ObjectManager::Initialize() {
	for (int _i = 0; _i < N_PLAYER; ++_i)
		obj_player_[_i]->Initialize(_i);

	for (int _i = 0; _i < N_BALL; ++_i)
		obj_ball_[_i]->Initialize(_i);

	for (int _i = 0; _i < N_WIRE; ++_i)
		obj_wire_[_i]->Initialize(_i);
}

void ObjectManager::LoadAssets() {
	mod_wire_ = DX9::Model::CreateBox(DXTK->Device9, 13.75f, 2.35f, 1.0f);

	mod_ball_ = DX9::Model::CreateFromFile(DXTK->Device9, L"_Models\\_Ball\\ball.X");
	mod_ball_->SetScale(GAME_CONST.BA_SCALE);
	mod_ball_->SetMaterial(ObjectBase::GetNomMaterial());
	
	for (int _i = 0; _i < N_PLAYER; ++_i)
		obj_player_[_i]->LoadAssets(USFN::MOD_PLAYER[DontDestroy->ChoseColor_[_i]]);

	for (ObjectBase* obj : obj_ball_)
		obj->LoadAssets(mod_ball_);

	for (ObjectBase* obj : obj_wire_)
		obj->LoadAssets(L"");
}

void ObjectManager::Update(const float deltaTime) {
	for (ObjectBase* obj : obj_player_)
		obj->Update(deltaTime);

	for (ObjectBase* obj : obj_ball_)
		obj->Update(deltaTime);

	// ゴールを用いるモードのみ回す
	if (DontDestroy->GameMode_ == DontDestroy->isGAMES_WITH_GOALS())
		for (ObjectBase* obj : obj_wire_)
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

	for (ObjectBase* obj : obj_ball_)
		physics_world_->addRigidBody(obj->myRigidbody());

	for (ObjectBase* obj : obj_wire_)
		physics_world_->addRigidBody(obj->myRigidbody());
}

void ObjectManager::RemoveWorld(btDynamicsWorld* physics_world_) {
	for (int _i = N_WIRE - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(obj_wire_[_i]->myRigidbody());
	
	for (int _i = N_BALL - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(obj_ball_[_i]->myRigidbody());

	for (int _i = N_PLAYER - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(obj_player_[_i]->myRigidbody());
}

int ObjectManager::PlayerLife(int index) {
	assert((0 <= index) && "ObjectManager::PlayerLife() : 指定したindexが不正です(負の値になっている)");
	return obj_player_[index]->myLife();
}

Vector2 ObjectManager::PlayerHandsPos(int index) {
	assert((0 <= index) && "ObjectManager::PlayerHandPos() : 指定したindexが不正です(負の値になっている)");
	return obj_player_[index]->Get_HandPos();
}

ObjectBase* ObjectManager::TheClosestPlayer(const int id, const Vector2 pos, float& comparison) {
	ObjectBase* _obj = nullptr;  // 一番近いオブジェクト
	Vector2 _target;  // 現在調べている座標
	float _new_comparison;  // 現在調べている距離
	float _min_comparison = 99.0f;  // 一番近い距離

	for (ObjectBase* obj : obj_player_) {
		if ((90.0f <= obj->myPosition().x) && (90.0f <= obj->myPosition().y))
			continue;

		if (obj->myObjectID() == id)
			continue;

		_new_comparison = _new_comparison = Comparison2Vector(pos, obj->myPosition());

		if (_new_comparison < _min_comparison) {
			_min_comparison = _new_comparison;
			_obj = obj;
		}
	}

	comparison = _min_comparison;

	return _obj;
}

ObjectBase* ObjectManager::TheClosestBall(const Vector2 pos, float& comparison) {
	ObjectBase* _obj = nullptr;  // 一番近いオブジェクト
	Vector2 _target;  // 現在調べている座標
	float _new_comparison;  // 現在調べている距離
	float _min_comparison = 99.0f;  // 一番近い距離

	for (ObjectBase* obj : obj_ball_) {
		if ((obj->myPosition().x == pos.x) && (obj->myPosition().y == pos.y))
			continue;

		_new_comparison = Comparison2Vector(pos, obj->myPosition());

		if (_new_comparison < _min_comparison) {
			_min_comparison = _new_comparison;
			_obj = obj;
		}
	}

	comparison = _min_comparison;

	return _obj;
}

float ObjectManager::Comparison2Vector(const Vector2 p1, const Vector2 p2) {
	return std::sqrtf(std::powf(p1.x - p2.x, 2) + std::powf(p1.y - p2.y, 2));
}