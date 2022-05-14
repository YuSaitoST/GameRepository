#include "ObjectManager.h"
#include "_Classes/FileNames.h"
#include "DontDestroyOnLoad.h"

CellList cellList = CellList{};

ObjPlayer* ObjectManager::obj_player_[N_PLAYER];
std::vector<ObjBall*> ObjectManager::obj_ball_;
ObjWire* ObjectManager::obj_wire_[N_WIRE];

ObjectManager::ObjectManager() {
	N_BALL = BALLS[(int)DontDestroy->GameMode_.SelectionMode()];

	obj_ball_.reserve(N_BALL);

	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i]		= new ObjPlayer((OPERATE_TYPE)((int)DontDestroy->charaType_[_i]), POS_START[_i], 1.0f);
		obj_player_[_i + 1] = new ObjPlayer((OPERATE_TYPE)((int)DontDestroy->charaType_[_i + 1]), POS_START[_i + 1], 1.0f);
		obj_wire_[_i]		= new ObjWire(POS_WIRE[_i], 1.0f);
		obj_wire_[_i + 1]	= new ObjWire(POS_WIRE[_i + 1], 1.0f);
	}

	for (int _i = 0; _i < N_BALL; ++_i)
		obj_ball_.push_back(new ObjBall(Vector3(99.0f, 99.0f, 0.0f), 1.0f));
}

ObjectManager::~ObjectManager() {
	for (int _i = N_WIRE - 1; 0 <= _i; --_i)
		obj_ball_.erase(obj_ball_.begin() + _i);

	for (int _i = N_WIRE - 1; 0 <= _i; --_i)
		delete obj_wire_[_i];
	
	for (int _i = N_PLAYER - 1; 0 <= _i; --_i)
		delete obj_player_[_i];
}

void ObjectManager::Initialize() {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i]->Initialize(_i);
		obj_player_[_i + 1]->Initialize(_i + 1);
	}

	for (int _i = 0; _i < N_BALL; ++_i)
		obj_ball_[_i]->Initialize(_i);

	const int _WIRE = N_WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		obj_wire_[_i]->Initialize(_i);
		obj_wire_[_i + 1]->Initialize(_i + 1);
	}
}

void ObjectManager::LoadAssets() {
	mod_wire_ = DX9::Model::CreateBox(DXTK->Device9, 13.75f, 2.35f, 1.0f);
	mod_ball_ = DX9::Model::CreateFromFile(DXTK->Device9, L"_Models\\_Ball\\ball.X");
	mod_ball_->SetScale(GAME_CONST.BA_SCALE);
	mod_ball_->SetMaterial(ObjectBase::GetNomMaterial());
	
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i]->LoadAssets(USFN::MOD_PLAYER[DontDestroy->ChoseColor_[_i]]);
		obj_wire_[_i]->LoadAssets(L"");

		obj_player_[_i + 1]->LoadAssets(USFN::MOD_PLAYER[DontDestroy->ChoseColor_[_i + 1]]);
		obj_wire_[_i + 1]->LoadAssets(L"");
	}

	for (ObjectBase* obj : obj_ball_)
		obj->LoadAssets(mod_ball_);
}

void ObjectManager::Update(const float deltaTime) {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i		]->Update(deltaTime);
		obj_player_[_i + 1	]->Update(deltaTime);
	}

	for (ObjectBase* obj : obj_ball_)
		obj->Update(deltaTime);

	// �S�[����p���郂�[�h�̂݉�
	if (DontDestroy->GameMode_.isGAMES_WITH_GOALS()) {
		const int _WIRE = N_WIRE * 0.5f;
		for (int _i = 0; _i <= _WIRE; _i += 2) {
			obj_wire_[_i	]->Update(deltaTime);
			obj_wire_[_i + 1]->Update(deltaTime);
		}
	}
}

void ObjectManager::RenderModels() {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		obj_player_[_i		]->Render();
		obj_player_[_i + 1	]->Render();
	}

	for (ObjectBase* obj : obj_ball_)
		obj->Render(mod_ball_);
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

void ObjectManager::AddWorld(btDynamicsWorld* physics_world_) {
	const int _PLAYER = N_PLAYER * 0.5f;
	for (int _i = 0; _i <= _PLAYER; _i += 2) {
		physics_world_->addRigidBody(obj_player_[_i]->myRigidbody());
		physics_world_->addRigidBody(obj_player_[_i + 1]->myRigidbody());
	}

	for (ObjectBase* obj : obj_ball_)
		physics_world_->addRigidBody(obj->myRigidbody());

	const int _WIRE = N_WIRE * 0.5f;
	for (int _i = 0; _i <= _WIRE; _i += 2) {
		physics_world_->addRigidBody(obj_wire_[_i]->myRigidbody());
		physics_world_->addRigidBody(obj_wire_[_i + 1]->myRigidbody());
	}
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
		// �����������疳��
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