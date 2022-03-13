#pragma once

#include "_Object/ObjectBase.h"
#include "_Object/_Player/ObjPlayer.h"
#include "_Object/_Ball/ObjBall.h"

class ObjectManager {
private:
	const int N_PLAYER	= 2;
	const int N_BALL	= 1;

	const float POS_X	= 13.0f;
	const float POS_Y	= 6.0f;

	const Vector3 POS_START[4] = {
		Vector3(-POS_X,	POS_Y, 0.0f),
		Vector3(POS_X,	POS_Y, 0.0f),
		Vector3(-POS_X, -POS_Y, 0.0f),
		Vector3(POS_X,  -POS_Y, 0.0f)
	};

	const std::wstring PLAYER_FILENAME[4] = {
		L"_Models\\_Player\\player_g.X",
		L"_Models\\_Player\\player_p.X",
		L"_Models\\_Player\\player_r.X",
		L"_Models\\_Player\\player_y.X"
	};

public:
	ObjectManager();
	virtual ~ObjectManager();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void RenderModels();
	void RenderSprites();

	void AddWorld(btDynamicsWorld* physics_world_);
	void RemoveWorld(btDynamicsWorld* physics_world_);

	static Vector2 PlayerHandsPos(int index);

	// 自分から一番近いプレイヤーの方向を返す
	static Vector2 TheClosestPlayerPos(Vector2 pos);
	// 自分から一番近いボールの方向を返す
	static Vector2 TheClosestBallPos(Vector2 pos);

private:
	static Vector2 TheClosestPos(ObjectBase* targetObj, Vector2 pos);

	static ObjPlayer* obj_player_[2];
	static ObjBall* obj_ball_[1];
	static ObjectBase* obj_wire_[4];

	DX9::MODEL mod_ball_;
};