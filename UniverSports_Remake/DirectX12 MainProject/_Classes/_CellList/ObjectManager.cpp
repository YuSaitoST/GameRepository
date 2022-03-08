#include "ObjectManager.h"

ObjectBase* ObjectManager::obj_player_[2];
ObjectBase* ObjectManager::obj_ball_[1];
ObjectBase* ObjectManager::obj_wire_[4];

ObjectManager::ObjectManager() {
	obj_player_[0] = new ObjPlayer(OPERATE_TYPE::MANUAL, POS_START[0], 1.0f);
	obj_player_[1] = new ObjPlayer(OPERATE_TYPE::COMPUTER, POS_START[1], 1.0f);

	obj_ball_[0] = new ObjBall(Vector3(99.0f, 99.0f, 0.0f), 1.0f);
}

ObjectManager::~ObjectManager() {
	delete obj_ball_[0];
	
	delete obj_player_[1];
	delete obj_player_[0];
}

void ObjectManager::Initialize() {
	for (int _i = 0; _i < 2; _i++)
		obj_player_[_i]->Initialize(_i);

	obj_ball_[0]->Initialize(0);
}

void ObjectManager::LoadAssets() {
	mod_ball_ = DX9::Model::CreateFromFile(DXTK->Device9, L"_Models\\_Ball\\ball.X");
	mod_ball_->SetScale(GAME_CONST.BA_SCALE);
	mod_ball_->SetMaterial(ObjectBase::GetNomMaterial());

	for (int _i = 0; _i < 2; _i++)
		obj_player_[_i]->LoadAssets(PLAYER_FILENAME[_i]);

	obj_ball_[0]->LoadAssets(mod_ball_);
}

void ObjectManager::Update(const float deltaTime) {
	for (ObjectBase* obj : obj_player_)
		obj->Update(deltaTime);

	obj_ball_[0]->Update(deltaTime);
}

void ObjectManager::RenderModels() {
	for (ObjectBase* obj : obj_player_)
		obj->Render();

	obj_ball_[0]->Render(mod_ball_);
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
	Vector2 _position = Vector2(99.0f, 99.0f);  // ��ԋ߂����W
	Vector2 _target;  // ���ݒ��ׂĂ�����W
	float _new_comparison;  // ���ݒ��ׂĂ��鋗��
	float _min_comparison = 99.0f;  // ��ԋ߂�����

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

// �܂��{�[���͎������Ă��Ȃ����߁A�x�[�X�����c���Ă���
Vector2 ObjectManager::TheClosestBallPos(Vector2 pos) {
	return Vector2::Zero;
}