#include "ObjectManager.h"
#include "_Classes/_FileNames/FileNames.h"
#include "DontDestroyOnLoad.h"
#include "_BallsInstructor/BallsInstructor.h"

CellList cellList = CellList{};

ObjPlayer* ObjectManager::obj_player_[N_PLAYER];
ObjWire* ObjectManager::obj_wire_[N_WIRE];

ObjectManager::ObjectManager() {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i]		= new ObjPlayer((OPERATE_TYPE)((int)DontDestroy->charaType_[_i]), POS_START[_i], 1.0f);
		obj_player_[_i + 1] = new ObjPlayer((OPERATE_TYPE)((int)DontDestroy->charaType_[_i + 1]), POS_START[_i + 1], 1.0f);
		obj_wire_[_i]		= new ObjWire(POS_WIRE[_i], 1.0f);
		obj_wire_[_i + 1]	= new ObjWire(POS_WIRE[_i + 1], 1.0f);
	}

	ballList_ = new BallList();
}

ObjectManager::~ObjectManager() {
	delete ballList_;

	for (int _i = N_WIRE - 1; 0 <= _i; --_i)
		delete obj_wire_[_i];
	
	for (int _i = N_PLAYER - 1; 0 <= _i; --_i)
		delete obj_player_[_i];
}

void ObjectManager::Initialize() {
	ballList_->Initialize();

	//インストラクターの初期化
	BallsInstructor* instructor = new BallsInstructor();
	instructor->SetBallList(ballList_->GetList());
	instructor->Initialize();

	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i]->Initialize(_i);
		obj_player_[_i]->SetInstructor(instructor);
		obj_player_[_i + 1]->Initialize(_i + 1);
		obj_player_[_i + 1]->SetInstructor(instructor);
	}

	const int _WIRE = N_WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		obj_wire_[_i]->Initialize(_i);
		obj_wire_[_i + 1]->Initialize(_i + 1);
	}
}

void ObjectManager::LoadAssets() {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i]->LoadAssets(USFN_MOD::PLAYER[DontDestroy->ChoseColor_[_i]]);
		obj_wire_[_i]->LoadAssets(L"");

		obj_player_[_i + 1]->LoadAssets(USFN_MOD::PLAYER[DontDestroy->ChoseColor_[_i + 1]]);
		obj_wire_[_i + 1]->LoadAssets(L"");
	}

	ballList_->LoadAssets();
}

void ObjectManager::Update(const float deltaTime) {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i		]->Update(deltaTime);
		obj_player_[_i + 1	]->Update(deltaTime);
	}

	ballList_->Update(deltaTime);

	const int _WIRE = N_WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		obj_wire_[_i]->Update(deltaTime);
		obj_wire_[_i + 1]->Update(deltaTime);
	}
}

void ObjectManager::RenderModels() {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i		]->Render();
		obj_player_[_i + 1	]->Render();
	}

	ballList_->Render();
}

void ObjectManager::RenderSprites() {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i		]->UIRender();
		obj_player_[_i + 1	]->UIRender();
	}
}

void ObjectManager::RenderAlphas() {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i		]->AlphaRender();
		obj_player_[_i + 1	]->AlphaRender();
	}
}

/**
* @brief ワールドに登録する
* @param physics_world 物理演算のワールド
*/
void ObjectManager::AddWorld(btDynamicsWorld* physics_world_) {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		physics_world_->addRigidBody(obj_player_[_i]->myRigidbody());
		physics_world_->addRigidBody(obj_player_[_i + 1]->myRigidbody());
	}

	ballList_->AddWorld(physics_world_);

	const int _WIRE = N_WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		physics_world_->addRigidBody(obj_wire_[_i]->myRigidbody());
		physics_world_->addRigidBody(obj_wire_[_i + 1]->myRigidbody());
	}
}

/**
* @brief ワールドから削除する
* @param physics_world 物理演算のワールド
*/
void ObjectManager::RemoveWorld(btDynamicsWorld* physics_world_) {
	for (int _i = N_WIRE - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(obj_wire_[_i]->myRigidbody());
	
	ballList_->RemoveWorld(physics_world_);

	for (int _i = N_PLAYER - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(obj_player_[_i]->myRigidbody());
}

/**
* @brief プレイヤーの残機を返す
* @param index プレイヤーの番号
* @return プレイヤーの残機
*/
int ObjectManager::PlayerLife(int index) {
	assert((0 <= index) && "ObjectManager::PlayerLife() : 指定したindexが不正です(負の値になっている)");
	return obj_player_[index]->myLife();
}

/**
* @brief プレイヤーの手元の座標を返す
* @param index プレイヤーの番号
* @return 手元の座標
*/
Vector2 ObjectManager::PlayerHandsPos(int index) {
	assert((0 <= index) && "ObjectManager::PlayerHandPos() : 指定したindexが不正です(負の値になっている)");
	return obj_player_[index]->Get_HandPos();
}

/**
* @brief 2つの座標の距離を調べる
* @param p1 自身の座標
* @param p2 相手の座標
* @return 距離
*/
float ObjectManager::Distance2Vector(const Vector2 p1, const Vector2 p2) {
	return std::sqrtf(std::powf(p1.x - p2.x, 2) + std::powf(p1.y - p2.y, 2));
}