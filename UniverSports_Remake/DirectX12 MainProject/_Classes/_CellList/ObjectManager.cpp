#include "ObjectManager.h"
#include "_Classes/FileNames.h"
#include "DontDestroyOnLoad.h"

ObjPlayer* ObjectManager::obj_player_[N_PLAYER];
ObjBall* ObjectManager::obj_ball_[N_BALL];
ObjWire* ObjectManager::obj_wire_[N_WIRE];

ObjectManager::ObjectManager() {
	DontDestroy->Survivor_ = (DontDestroy->isDODGEBALL_2ON2()) ? N_PLAYER / 2 : N_PLAYER;

	obj_player_[0] = new ObjPlayer(OPERATE_TYPE::MANUAL, POS_START[0], 1.0f);
	obj_player_[1] = new ObjPlayer(OPERATE_TYPE::COMPUTER, POS_START[1], 1.0f);
	//obj_player_[2] = new ObjPlayer(OPERATE_TYPE::COMPUTER, POS_START[2], 1.0f);
	//obj_player_[3] = new ObjPlayer(OPERATE_TYPE::COMPUTER, POS_START[3], 1.0f);

	for (int _i = 0; _i < N_BALL; ++_i)
		obj_ball_[_i] = new ObjBall(Vector3(99.0f, 99.0f, 0.0f), 1.0f);

	for (int _i = 0; _i < N_WIRE; ++_i)
		obj_wire_[_i] = new ObjWire(POS_WIRE[_i], 1.0f);

#ifdef DEBUG
	int size_p = sizeof(new ObjPlayer());
	int size_p0 = sizeof(obj_player_[0]);
	int size_b = sizeof(new ObjBall());
	int size_b0 = sizeof(obj_ball_[0]);
	int size_w = sizeof(new ObjWire());
	int size_w0 = sizeof(obj_wire_[0]);
#endif // DEBUG

}

ObjectManager::~ObjectManager() {
	for (int _i = N_WIRE - 1; 0 <= _i; --_i)
		delete obj_wire_[_i];

	for (int _i = N_BALL - 1; 0 <= _i; --_i)
		delete obj_ball_[_i];
	
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
	assert((0 <= index) && "ObjectManager::PlayerLife() : �w�肵��index���s���ł�(���̒l�ɂȂ��Ă���)");
	return obj_player_[index]->myLife();
}

Vector2 ObjectManager::PlayerHandsPos(int index) {
	assert((0 <= index) && "ObjectManager::PlayerHandPos() : �w�肵��index���s���ł�(���̒l�ɂȂ��Ă���)");
	return obj_player_[index]->Get_HandPos();
}

ObjectBase* ObjectManager::TheClosestPlayer(const int id, const Vector2 pos, float& comparison) {
	ObjectBase* _obj = nullptr;  // ��ԋ߂��I�u�W�F�N�g
	Vector2 _target;  // ���ݒ��ׂĂ�����W
	float _new_comparison;  // ���ݒ��ׂĂ��鋗��
	float _min_comparison = 99.0f;  // ��ԋ߂�����

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
	ObjectBase* _obj = nullptr;  // ��ԋ߂��I�u�W�F�N�g
	Vector2 _target;  // ���ݒ��ׂĂ�����W
	float _new_comparison;  // ���ݒ��ׂĂ��鋗��
	float _min_comparison = 99.0f;  // ��ԋ߂�����

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