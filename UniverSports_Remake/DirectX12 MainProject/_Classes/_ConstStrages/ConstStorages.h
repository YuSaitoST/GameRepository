#pragma once


#include <cstdio>
#include <cassert>

#define GAME_CONST ConstStorageC::GetInstance()

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


	const int FieldSide_X = 32;
	const int FieldSide_Y = 18;
	
	const int MODE_1_TIME = 120;

	const float PL_POS_X = 13.0f;
	const float PL_POS_Y = 6.0f;

	const float PL_AIMING_DISTANCE = 25.0f;  // 射程距離
	const float PL_AIMING_CORRECTION = 1.5f;  // 敵の移動予想分

	const int Move_FirSpeed = 30;		// * 0.01f必要  ,  速度補正、これないと操作重い
	
	const int Player_MAX = 4;
	const int Player_FacingRight = -90;
	const int Player_FacingLeft = 90;
	const int Player_BlowPower = 50;

	const int Ball_Radius = 2;


	const int BallMax_ = 5;
	const int BallMax_Hand = 10;

	const int BALLMAX[4] = { 5,10,5,6 };
};