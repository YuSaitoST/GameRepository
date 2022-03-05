#pragma once

#include "_Object/ObjectBase.h"
#include "_Object/_Player/ObjPlayer.h"

class ObjectManager {
public:
	ObjectManager();
	virtual ~ObjectManager();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void RenderModels();
	void RenderSprites();  // ����g��Ȃ����A�Q�[�W��UI�ɕK�v

	void AddWorld(btDynamicsWorld* physics_world_);
	void RemoveWorld(btDynamicsWorld* physics_world_);

	// ���������ԋ߂��v���C���[�̕�����Ԃ�
	static Vector2 TheClosestPlayerPos(Vector2 pos);
	// ���������ԋ߂��{�[���̕�����Ԃ�
	static Vector2 TheClosestBallPos(Vector2 pos);

private:
	static ObjectBase* obj_player_[2];

private:
	const std::wstring PLAYER_FILENAME[4] = {
		L"_Models\\Player\\player_g.X",
		L"_Models\\Player\\player_p.X",
		L"_Models\\Player\\player_r.X",
		L"_Models\\Player\\player_y.X"
	};

	const Vector3 POS_START[4] = {
		Vector3(-13.0f,	6.0f, 0.0f),
		Vector3(13.0f,	6.0f, 0.0f),
		Vector3(-13.0f, -6.0f, 0.0f),
		Vector3(13.0f,  -6.0f, 0.0f)
	};
};