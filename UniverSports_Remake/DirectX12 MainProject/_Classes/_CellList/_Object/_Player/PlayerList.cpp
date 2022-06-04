#include "PlayerList.h"
#include "_Classes/_FileNames/FileNames.h"
#include "DontDestroyOnLoad.h"

PlayerList::PlayerList() {
	// �������m��
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
* @brief ���[���h�ɓo�^����
* @param physics_world �������Z�̃��[���h
*/
void PlayerList::AddWorld(btDynamicsWorld* physics_world_) {
	for (ObjPlayer* obj : list_)
		physics_world_->addRigidBody(obj->myRigidbody());
}

/**
* @brief ���[���h����폜����
* @param physics_world �������Z�̃��[���h
*/
void PlayerList::RemoveWorld(btDynamicsWorld* physics_world_) {
	for (int _i = N_PLAYER - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(list_[_i]->myRigidbody());
}

/**
* @brief �C���X�g���N�^�[�̐ݒ�
* @param blInstructor �{�[���̃C���X�g���N�^�[
* @param plInstructor �v���C���[�̃C���X�g���N�^�[
*/
void PlayerList::SetInstructors(BallsInstructor* blInstructor, PlayersInstructor* plInstuructor) {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		list_[_i]->SetInstructor(blInstructor, plInstuructor);
		list_[_i + 1]->SetInstructor(blInstructor, plInstuructor);
	}
}

/**
* @brief �v���C���[�̎c�@��Ԃ�
* @param index �v���C���[�̔ԍ�
* @return �v���C���[�̎c�@
*/
int PlayerList::PlayerLife(int index) {
	return list_[index]->myLife();
}

///**
//* @brief �v���C���[�̎茳�̍��W��Ԃ�
//* @param index �v���C���[�̔ԍ�
//* @return �茳�̍��W
//*/
//XMFLOAT2 PlayerList::PlayerHandsPos(int index) {
//	return list_[index]->Get_HandPos();
//}