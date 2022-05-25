#include "BallList.h"
#include "_Classes/_FileNames/FileNames.h"
#include "DontDestroyOnLoad.h"

BallList::BallList() {
	// 使用するボールの個数を決める
	N_BALL = BALLS[(int)DontDestroy->GameMode_.SelectionMode()];

	// メモリ確保
	list_.reserve(N_BALL);

	for (int _i = 0; _i < N_BALL; ++_i)
		list_.push_back(new ObjBall(Vector3(99.0f, 99.0f, 0.0f), 1.0f));
}

BallList::~BallList() {
	for (int _i = N_BALL - 1; 0 <= _i; --_i)
		list_.erase(list_.begin() + _i);
}

void BallList::Initialize() {
	for (int _i = 0; _i < N_BALL; ++_i)
		list_[_i]->Initialize(_i);
}

void BallList::LoadAssets() {
	model_ = DX9::Model::CreateFromFile(DXTK->Device9, USFN_MOD::BALL.c_str());
	model_->SetScale(GAME_CONST.BA_SCALE);
	model_->SetMaterial(ObjectBase::GetNomMaterial());

	for (ObjectBase* obj : list_)
		obj->LoadAssets(model_);
}

void BallList::Update(const float deltaTime) {
	for (ObjectBase* obj : list_)
		obj->Update(deltaTime);
}

void BallList::Render() {
	for (ObjectBase* obj : list_)
		obj->Render(model_);
}

/**
* @brief ワールドに登録する
* @param physics_world 物理演算のワールド
*/
void BallList::AddWorld(btDynamicsWorld* physics_world_) {
	for (ObjectBase* obj : list_)
		physics_world_->addRigidBody(obj->myRigidbody());
}

/**
* @brief ワールドから削除する
* @param physics_world 物理演算のワールド
*/
void BallList::RemoveWorld(btDynamicsWorld* physics_world_) {
	for (int _i = N_BALL - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(list_[_i]->myRigidbody());
}