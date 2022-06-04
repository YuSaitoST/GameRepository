#include "PlayerList.h"
#include "_Classes/_FileNames/FileNames.h"
#include "DontDestroyOnLoad.h"

PlayerList::PlayerList() {
	// メモリ確保
	list_.reserve(N_PLAYER);

	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		list_.push_back(new ObjPlayer((OPERATE_TYPE)((int)DontDestroy->charaType_[_i]), POS_START[_i], 1.0f));
		list_.push_back(new ObjPlayer((OPERATE_TYPE)((int)DontDestroy->charaType_[_i + 1]), POS_START[_i + 1], 1.0f));
	}
}

PlayerList::~PlayerList() {
	for (int _i = N_PLAYER - 1; 0 <= _i; --_i)
		list_.erase(list_.begin() + _i);
}

void PlayerList::Initialize() {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		list_[_i]->Initialize(_i);
		list_[_i + 1]->Initialize(_i + 1);
	}
}

void PlayerList::LoadAssets() {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		list_[_i]->LoadAssets(USFN_MOD::PLAYER[DontDestroy->ChoseColor_[_i]]);
		list_[_i + 1]->LoadAssets(USFN_MOD::PLAYER[DontDestroy->ChoseColor_[_i + 1]]);
	}
}

void PlayerList::Update(const float deltaTime) {
	for (ObjPlayer* obj : list_)
		obj->Update(deltaTime);
}

void PlayerList::RenderModel() {
	for (ObjPlayer* obj : list_)
		obj->Render();
}

void PlayerList::RenderSprite() {
	for (ObjPlayer* obj : list_)
		obj->UIRender();
}

void PlayerList::RenderTransparency() {
	for (ObjPlayer* obj : list_)
		obj->AlphaRender();
}

/**
* @brief ワールドに登録する
* @param physics_world 物理演算のワールド
*/
void PlayerList::AddWorld(btDynamicsWorld* physics_world_) {
	for (ObjPlayer* obj : list_)
		physics_world_->addRigidBody(obj->myRigidbody());
}

/**
* @brief ワールドから削除する
* @param physics_world 物理演算のワールド
*/
void PlayerList::RemoveWorld(btDynamicsWorld* physics_world_) {
	for (int _i = N_PLAYER - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(list_[_i]->myRigidbody());
}

/**
* @brief インストラクターの設定
* @param blInstructor ボールのインストラクター
* @param plInstructor プレイヤーのインストラクター
*/
void PlayerList::SetInstructors(BallsInstructor* blInstructor, PlayersInstructor* plInstuructor) {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		list_[_i]->SetInstructor(blInstructor, plInstuructor);
		list_[_i + 1]->SetInstructor(blInstructor, plInstuructor);
	}
}

/**
* @brief プレイヤーの残機を返す
* @param index プレイヤーの番号
* @return プレイヤーの残機
*/
int PlayerList::PlayerLife(int index) {
	return list_[index]->myLife();
}

///**
//* @brief プレイヤーの手元の座標を返す
//* @param index プレイヤーの番号
//* @return 手元の座標
//*/
//XMFLOAT2 PlayerList::PlayerHandsPos(int index) {
//	return list_[index]->Get_HandPos();
//}