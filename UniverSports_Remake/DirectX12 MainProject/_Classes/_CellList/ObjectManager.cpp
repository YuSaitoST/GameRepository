#include "ObjectManager.h"
#include "_Classes/_FileNames/FileNames.h"
#include "DontDestroyOnLoad.h"
#include "_BallsInstructor/BallsInstructor.h"

CellList cellList = CellList{};

ObjectManager::ObjectManager() {
	playerList_		= new PlayerList();
	ballList_		= new BallList();
	plInstructor_	= new PlayersInstructor();
	icon_animator_	= std::make_unique<IconAnimator>();

	const int _WIRE = OBJECT_MAX::WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		obj_wire_[_i]		= new ObjWire(POS_WIRE[_i], 1.0f);
		obj_wire_[_i + 1]	= new ObjWire(POS_WIRE[_i + 1], 1.0f);
	}
}

ObjectManager::~ObjectManager() {
	for (int _i = OBJECT_MAX::WIRE - 1; 0 <= _i; --_i)
		delete obj_wire_[_i];

	delete plInstructor_;
	delete ballList_;
	delete playerList_;
}

void ObjectManager::Initialize() {
	playerList_->Initialize();
	ballList_->Initialize();

	//インストラクターの初期化
	std::unique_ptr<BallsInstructor> ballsInstructor = std::make_unique<BallsInstructor>();
	ballsInstructor->Initialize(ballList_->GetList());
	plInstructor_->Initialize(playerList_->GetList());

	playerList_->SetInstructors(ballsInstructor.release(), plInstructor_);

	const int _WIRE = OBJECT_MAX::WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		obj_wire_[_i]->Initialize(_i);
		obj_wire_[_i + 1]->Initialize(_i + 1);
	}
}

void ObjectManager::LoadAssets() {
	const int _WIRE = OBJECT_MAX::WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		obj_wire_[_i]->LoadAssets(L"");
		obj_wire_[_i + 1]->LoadAssets(L"");
	}

	playerList_->LoadAssets();
	ballList_->LoadAssets();
	icon_animator_->LoadAssets();
}

void ObjectManager::Update(const float deltaTime) {
	playerList_->Update(deltaTime);
	ballList_->Update(deltaTime);

	const int _WIRE = OBJECT_MAX::WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		obj_wire_[_i]->Update(deltaTime);
		obj_wire_[_i + 1]->Update(deltaTime);
	}

	icon_animator_->Update(deltaTime);
}

void ObjectManager::RenderModels() {
	playerList_->RenderModel();
	ballList_->Render();
}

void ObjectManager::RenderSprites() {
	playerList_->RenderSprite();

	 //PlayerList調整後解放
	if (!DontDestroy->GameMode_.isGAMES_WITH_GOALS()) {
		for (int _i = 0; _i <= 2; _i += 2) {
			icon_animator_->Render(playerList_->PlayerLife(_i), _i);
			icon_animator_->Render(playerList_->PlayerLife(_i + 1), _i + 1);
		}
	}
}

void ObjectManager::RenderAlphas() {
	playerList_->RenderTransparency();
}

/**
* @brief ワールドに登録する
* @param physics_world 物理演算のワールド
*/
void ObjectManager::AddWorld(btDynamicsWorld* physics_world_) {
	playerList_->AddWorld(physics_world_);
	ballList_->AddWorld(physics_world_);

	const int _WIRE = OBJECT_MAX::WIRE * 0.5f;
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
	for (int _i = OBJECT_MAX::WIRE - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(obj_wire_[_i]->myRigidbody());
	
	ballList_->RemoveWorld(physics_world_);
	playerList_->RemoveWorld(physics_world_);
}