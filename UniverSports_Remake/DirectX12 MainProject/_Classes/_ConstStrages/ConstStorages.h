/**
 * @file ConstStorage.h
 * @brief パラメータークラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "UIPosition.h"

//マクロ
#define GAME_CONST ConstStorageC::GetInstance()
#define GAMES_PARAM ConstStorageC::GetInstance().GetGameProgression()
#define PLAYER_PARAM ConstStorageC::GetInstance().GetPlayerParam()
#define BALL_PARAM ConstStorageC::GetInstance().GetBallParam()
#define THRUSTER_PARAM ConstStorageC::GetInstance().GetThrusterParam()

namespace OBJECT_MAX {
	const int PLAYER = 4;
	const int WIRE = 4;

}  //namespace OBJECT_MAX

class ConstStorageC {
private:
	struct GameProgression {
		float TL_UI_DISPLAY;
		float TL_TIME_LOGO_DISPLAY;
		float TL_DEMO_PLAYBACK;
		float LB_MV_SCALE;
		float LB_TIME_AFTER_PREPARATION;
		float MN_TIME_HANDBALL;
		float FN_TIME_MOVE;
		float FN_TIME_DISPLAY;
		float FN_TIME_FADEOUT;
	};
	struct Player {
		float START_POS_X;
		float START_POS_Y;
		float Player_FacingRight;
		float SCALE;
		float SPEED_MAX_NORMAL;
		float SPEED_MAX_BOOST;
		float SPEED_MOVE;
		float POWER_THRUSTER;
		float TIME_RESPONE;
		float TIME_INVINCIBLE;

		DirectX::XMFLOAT3 START_POS[OBJECT_MAX::PLAYER];
	};
	struct Thruster {
		float SCALE[2];
		float MOVEMENT_NOMAL;
		float MOVEMENT_ACCEL;
		float AMOUNT_OF_DECREASE;
		float AMOUNT_OF_RECOVERY;
	};
	struct Ball {
		float MAX[4];
		float MOD_SCALE;
		float COL_SCALE;
		float SPEED_FLOAT;
		float SPEED_SHOT;
		float Z_CAUTCH;
	};

public:
	ConstStorageC() : gameParam_{ 0.0f }, playerParam_{ 0.0f }, ballParam_{ 0.0f }, thrusterParam_{ 0.0f } {};
	virtual ~ConstStorageC() {};

	static ConstStorageC& GetInstance()
	{
		static ConstStorageC Cs;
		return Cs;
	}

	void Initialize();
	GameProgression GetGameProgression() const { return gameParam_; }
	Player GetPlayerParam() const { return playerParam_; }
	Ball GetBallParam() const { return ballParam_; }
	Thruster GetThrusterParam() const { return thrusterParam_; }

private:
	GameProgression gameParam_;
	Player playerParam_;
	Ball ballParam_;
	Thruster thrusterParam_;
};