#pragma once


#include <cstdio>
#include <cassert>
#include "Base/pch.h"
#include "Base/dxtk.h"

#define GAME_CONST ConstStorageC::GetInstance()

using namespace DirectX::SimpleMath;

class ConstStorageC {
public:
	ConstStorageC() = default;
	virtual ~ConstStorageC() = default;

	static ConstStorageC& GetInstance()
	{
		static ConstStorageC Cs;
		return Cs;
	}

	void Initialize();

	float LB_GONEXT;

	float PL_SCALE;
	float PL_SPEED_MAX;
	float PL_SPEED_TURN;
	float PL_JET_MAX;
	float PL_POWER_JET;
	float PL_ReSponeTime;
	float PL_InvincibleTime;

	float JT_SCALE[2];
	float JT_MOVEMENT_NOMAL;
	float JT_MOVEMENT_ACCEL;
	float AMOUNT_OF_DECREASE;
	float AMOUNT_OF_RECOVERY;

	float BA_SCALE;
	float BA_SPEED_FLOAT;
	float BA_SPEED_SHOT;

	float FN_TIME_MOVE;
	float FN_TIME_DISPLAY;
	float FN_TIME_ALPHA;


	const float FieldSide_X = 32.0f;
	const float FieldSide_Y = 18.0f;
	
	const int MODE_1_TIME = 120;

	const float PL_POS_X = 13.0f;
	const float PL_POS_Y = 6.0f;

	const float PL_AIMING_DISTANCE = 25.0f;  // ŽË’ö‹——£
	const float PL_AIMING_CORRECTION = 1.5f;  // “G‚ÌˆÚ“®—\‘z•ª

	const float Move_FirSpeed = 7.5;
	
	const int Player_MAX = 4;
	const int Player_FacingRight = -90;
	const int Player_FacingLeft = 90;
	const int Player_BlowPower = 50;

	const int Ball_Radius = 2;


	const int BallMax_ = 5;
	const int BallMax_Hand = 10;

	const int BALLMAX[4] = { 5,10,5,6 };

	const Vector3 S_POS[4] = {
		Vector3(-13.0f,6.0f,0.f),
		Vector3(13.0f,6.0f,0.f),
		Vector3(-13.0f,-6.0f,0.f),
		Vector3(13.0f,-6.0f,0.f)
	};
};