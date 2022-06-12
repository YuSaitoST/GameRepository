#include "ObjectManager.h"
#include "_Classes/_FileNames/FileNames.h"
#include "DontDestroyOnLoad.h"
#include "_BallsInstructor/BallsInstructor.h"

CellList cellList = CellList{};

ObjectManager::ObjectManager() {
	playerList_		= std::make_unique<PlayerList>();
	ballList_		= std::make_unique<BallList>();
	wireList_		= std::make_unique<WireList>();
	icon_animator_	= std::make_unique<IconAnimator>();
}

void ObjectManager::Initialize() {
	playerList_->Initialize();
	ballList_->Initialize();
	wireList_->Initialize();

	//インストラクターの初期化
	BallsInstructor* _ballsInstructor = new BallsInstructor();
	_ballsInstructor->Initialize(ballList_->GetList());

	PlayersInstructor* _plInstructor = new PlayersInstructor();
	_plInstructor->Initialize(playerList_->GetList());

	playerList_->SetInstructors(_ballsInstructor, _plInstructor);
	wireList_->SetInstructors(_ballsInstructor, _plInstructor);
}

void ObjectManager::LoadAssets() {
	playerList_->LoadAssets();
	ballList_->LoadAssets();
	wireList_->LoadAssets();
	icon_animator_->LoadAssets();
}

void ObjectManager::Update(const float deltaTime) {
	playerList_->Update(deltaTime);
	ballList_->Update(deltaTime);
	wireList_->Update(deltaTime);
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
		const int _PLAYER = OBJECT_MAX::PLAYER * 0.5f;
		for (int _i = 0; _i <= _PLAYER; _i += 2) {
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
	wireList_->AddWorld(physics_world_);
}

/**
* @brief ワールドから削除する
* @param physics_world 物理演算のワールド
*/
void ObjectManager::RemoveWorld(btDynamicsWorld* physics_world_) {
	wireList_->RemoveWorld(physics_world_);
	ballList_->RemoveWorld(physics_world_);
	playerList_->RemoveWorld(physics_world_);
}