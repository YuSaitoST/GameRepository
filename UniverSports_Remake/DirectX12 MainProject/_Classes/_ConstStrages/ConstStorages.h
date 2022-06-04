#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#define GAME_CONST ConstStorageC::GetInstance()
#define GAMES_PARAM ConstStorageC::GetInstance().GetGameProgression()
#define PLAYER_PARAM ConstStorageC::GetInstance().GetPlayerParam()

using namespace DirectX::SimpleMath;

class ConstStorageC {
private:
	struct GameProgression {
		const float TL_DEMO_PLAYBACK = 10.0f;
		float LB_TIME_AFTER_PREPARATION;
		float MN_TIME_HANDBALL;
		float FN_TIME_MOVE;
		float FN_TIME_DISPLAY;
		float FN_TIME_FADEOUT;
	};
	struct Player {
		float SCALE;
		float SPEED_MAX_NORMAL;
		float SPEED_MAX_BOOST;
		float SPEED_MOVE;
		float POWER_THRUSTER;
		float TIME_RESPONE;
		float TIME_INVINCIBLE;
	};

public:
	ConstStorageC() {};
	virtual ~ConstStorageC() {};

	static ConstStorageC& GetInstance()
	{
		static ConstStorageC Cs;
		return Cs;
	}

	void Initialize();
	GameProgression GetGameProgression() const { return gameParams_; }
	Player GetPlayerParam() const { return playerParam_; }

	float JT_SCALE[2];
	float JT_MOVEMENT_NOMAL;
	float JT_MOVEMENT_ACCEL;
	float AMOUNT_OF_DECREASE;
	float AMOUNT_OF_RECOVERY;

	float BA_SCALE;
	float BA_SPEED_FLOAT;
	float BA_SPEED_SHOT;

	const float TITLE_UI_DISPLAY = 0.5f;
	const float	TITLE_TIME_LOGO_DISPLAY = 2.5f;

	const float PL_POS_X = 13.0f;
	const float PL_POS_Y = 6.0f;

	const float Move_FirSpeed = 7.5;
	
	const int Player_MAX = 4;
	const int Player_FacingRight = -90;

	const int BALLMAX[4] = { 5,10,5,6 };

	const Vector3 S_POS[4] = {
		Vector3(-13.0f,6.0f,0.f),
		Vector3(13.0f,6.0f,0.f),
		Vector3(-13.0f,-6.0f,0.f),
		Vector3(13.0f,-6.0f,0.f)
	};

private:
	GameProgression gameParams_;
	Player playerParam_;
};