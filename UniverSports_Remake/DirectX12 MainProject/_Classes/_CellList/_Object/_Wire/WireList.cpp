#include "WireList.h"

WireList::WireList() {
	list_.reserve(OBJECT_MAX::WIRE);

	const int _WIRE = OBJECT_MAX::WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		list_.push_back(new ObjWire(WIRE_PARAM.POS[_i], 1.0f));
		list_.push_back(new ObjWire(WIRE_PARAM.POS[_i + 1], 1.0f));
	}
}

WireList::~WireList() {
	for (int _i = OBJECT_MAX::WIRE - 1; 0 <= _i; --_i)
		list_.erase(list_.begin() + _i);
}

void WireList::Initialize() {
	const int _WIRE = OBJECT_MAX::WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		list_[_i]->Initialize(_i);
		list_[_i + 1]->Initialize(_i + 1);
	}
}

void WireList::LoadAssets() {
	const int _WIRE = OBJECT_MAX::WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		list_[_i]->LoadAssets(L"");
		list_[_i + 1]->LoadAssets(L"");
	}
}

void WireList::Update(const float deltaTime) {
	const int _WIRE = OBJECT_MAX::WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		list_[_i]->Update(deltaTime);
		list_[_i + 1]->Update(deltaTime);
	}
}

/**
* @brief ���[���h�ɓo�^����
* @param physics_world �������Z�̃��[���h
*/
void WireList::AddWorld(btDynamicsWorld* physics_world_) {
	for (ObjWire* obj : list_)
		physics_world_->addRigidBody(obj->myRigidbody());
}

/**
* @brief ���[���h����폜����
* @param physics_world �������Z�̃��[���h
*/
void WireList::RemoveWorld(btDynamicsWorld* physics_world_) {
	for (int _i = OBJECT_MAX::WIRE - 1; 0 <= _i; --_i)
		physics_world_->removeRigidBody(list_[_i]->myRigidbody());
}

/**
* @brief �C���X�g���N�^�[�̐ݒ�
* @param blInstructor �{�[���̃C���X�g���N�^�[
* @param plInstructor �v���C���[�̃C���X�g���N�^�[
*/
void WireList::SetInstructors(BallsInstructor* blInstructor, PlayersInstructor* plInstuructor) {
	const int _WIRE = OBJECT_MAX::WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		list_[_i]->SetInstructor(blInstructor, plInstuructor);
		list_[_i + 1]->SetInstructor(blInstructor, plInstuructor);
	}
}