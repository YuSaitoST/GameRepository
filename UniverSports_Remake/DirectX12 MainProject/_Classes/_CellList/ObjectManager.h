#pragma once

#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Object/ObjectBase.h"
#include "_Object/_Player/ObjPlayer.h"
#include "_Object/_Ball/ObjBall.h"
#include "_Object/_Wire/ObjWire.h"

class ObjectManager {
private:
	const int N_PLAYER	= 2;
	const int N_BALL	= 1;
	const int N_WIRE	= 4;

	const Vector3 POS_START[4] = {
		Vector3(-GAME_CONST.PL_POS_X, GAME_CONST.PL_POS_Y, 0.0f),
		Vector3(GAME_CONST.PL_POS_X,	GAME_CONST.PL_POS_Y, 0.0f),
		Vector3(-GAME_CONST.PL_POS_X, -GAME_CONST.PL_POS_Y, 0.0f),
		Vector3(GAME_CONST.PL_POS_X,  -GAME_CONST.PL_POS_Y, 0.0f)
	};

	const std::wstring PLAYER_FILENAME[4] = {
		L"_Models\\_Player\\player_g.X",
		L"_Models\\_Player\\player_p.X",
		L"_Models\\_Player\\player_r.X",
		L"_Models\\_Player\\player_y.X"
	};

	const float FX = 32.0f;
	const float FY = 18.0f;
	const float X = FX - 5.25f + 1.25f;
	const float Y = FY - 4.75f + 1.25f;

	const SimpleMath::Vector3 POS_WIRE[4] = {
		Vector3(-X, Y, 0.0f),
		Vector3(X,Y,0.0f),
		Vector3(X,-Y,0.0f),
		Vector3(-X,-Y,0.0f)
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

	static ObjectBase* TheClosestPlayer(const int id, const Vector2 pos, float& comparison);
	static ObjectBase* TheClosestBall(const Vector2 pos, float& comparison);

private:
	static float Comparison2Vector(const Vector2 p1, const Vector2 p2);

	static ObjPlayer* obj_player_[2];
	static ObjBall* obj_ball_[1];
	static ObjWire* obj_wire_[4];

	DX9::MODEL mod_ball_;
};