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
#include "USMaterial.h"

//マクロ
#define GAME_CONST		ConstStorageC::GetInstance()
#define GAMES_PARAM		ConstStorageC::GetInstance().GetGameProgression()
#define PLAYER_PARAM	ConstStorageC::GetInstance().GetPlayerParam()
#define BALL_PARAM		ConstStorageC::GetInstance().GetBallParam()
#define THRUSTER_PARAM	ConstStorageC::GetInstance().GetThrusterParam()
#define WIRE_PARAM		ConstStorageC::GetInstance().GetWireParam()

namespace OBJECT_MAX {
	const int PLAYER	= 4;
	const int WIRE		= 4;

}  //namespace OBJECT_MAX

class ConstStorageC {
private:
	struct GameProgression {
		float TL_UI_DISPLAY;
		float TL_TIME_LOGO_DISPLAY;
		float TL_DEMO_PLAYBACK;
		float LB_MV_SCALE;
		float LB_TIME_AFTER_PREPARATION;
		float MN_COUNTDOWN;
		float MN_GAMETIMER[4];
		float MN_FADEOUT;
		float FN_TIME_MOVE;
		float FN_TIME_DISPLAY;
		float FN_TIME_FADEOUT;
		float FN_FADEIN;
	};
	struct Player {
		float Player_FacingRight;
		float SCALE;
		float SPEED_MAX_NORMAL;
		float SPEED_MAX_BOOST;
		float SPEED[2];
		float TIME_RESPONE;
		float TIME_INVINCIBLE;
		DirectX::XMFLOAT3 START_POS[OBJECT_MAX::PLAYER];
		DirectX::XMFLOAT2 HAND_POS;
	};
	struct Thruster {
		float SCALE[2];
		float MOVEMENT_NOMAL;
		float MOVEMENT_ACCEL;
		float TIME_UPDATEPOSITION;
		float GAUGE_STOP;
		float AMOUNT_OF_DECREASE;
		float AMOUNT_OF_RECOVERY;
		float ROTATE_Y;
	};
	struct Ball {
		float MAX[4];
		float MOD_SCALE;
		float COL_SCALE;
		float OBJ_SCALE;
		float SPEED_FLOAT;
		float SPEED_SHOT;
		float SPEED_GOAL;
		float Z_AT_CAUTCH;
		float Z_AT_GOAL;
	};
	struct Wire {
		DirectX::XMFLOAT3 POS[OBJECT_MAX::WIRE];
		DirectX::XMFLOAT3 SCALE;
		float COLLIDER_SCALE_Y_CORRECTIONVALUE;
		float MOD_ROT_Z[OBJECT_MAX::WIRE];
		float BULLET_ROT_Z[OBJECT_MAX::WIRE];
	};

public:

	static ConstStorageC& GetInstance()
	{
		static ConstStorageC Cs;
		return Cs;
	}

	void Initialize();
	GameProgression	GetGameProgression	() const { return gameParam_;		}
	Player			GetPlayerParam		() const { return playerParam_;		}
	Ball			GetBallParam		() const { return ballParam_;		}
	Thruster		GetThrusterParam	() const { return thrusterParam_;	}
	Wire			GetWireParam		() const { return wireParam_;		}

private:
	ConstStorageC() : gameParam_{ 0.0f }, playerParam_{ 0.0f }, ballParam_{ 0.0f }, thrusterParam_{ 0.0f } {};
	virtual ~ConstStorageC() {};

	GameProgression	gameParam_;
	Player			playerParam_;
	Ball			ballParam_;
	Thruster		thrusterParam_;
	Wire			wireParam_;
};