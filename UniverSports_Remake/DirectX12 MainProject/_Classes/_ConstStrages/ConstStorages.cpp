#include "ConstStorages.h"
#include "_Classes/_LoadCSV/LoadCSV.h"

void ConstStorageC::Initialize() {
	CSV::Schan(L"_Parameters\\GameProgressionParameter.csv",
		"%f,%f,%f,%f,%f",
		&gameParams_.LB_TIME_AFTER_PREPARATION,
		&gameParams_.MN_TIME_HANDBALL,
		&gameParams_.FN_TIME_MOVE,
		&gameParams_.FN_TIME_DISPLAY,
		&gameParams_.FN_TIME_FADEOUT
	);
	CSV::Schan(L"_Parameters\\PlayersParameter.csv",
		"%f,%f,%f,%f,%f,%f,%f",
		&playerParam_.SCALE,
		&playerParam_.SPEED_MAX_NORMAL,
		&playerParam_.SPEED_MAX_BOOST,
		&playerParam_.SPEED_MOVE,
		&playerParam_.POWER_THRUSTER,
		&playerParam_.TIME_RESPONE,
		&playerParam_.TIME_INVINCIBLE
	);
	CSV::Schan(L"_Parameters\\ThrusterParameter.csv",
		"%f,%f,%f,%f,%f,%f",
		&JT_SCALE[0],
		&JT_SCALE[1],
		&JT_MOVEMENT_NOMAL,
		&JT_MOVEMENT_ACCEL,
		&AMOUNT_OF_DECREASE,
		&AMOUNT_OF_RECOVERY
	);
	CSV::Schan(L"_Parameters\\BallParameter.csv",
		"%f,%f,%f",
		&BA_SCALE,
		&BA_SPEED_FLOAT,
		&BA_SPEED_SHOT
	);
	//CSV::Schan(
	//	L"_Parameters\\paraList.csv",
	//	"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
	//	&LB_GONEXT,
	//	&PL_SCALE,
	//	&PL_SPEED_MAX,
	//	&PL_SPEED_TURN,
	//	&PL_JET_MAX,
	//	&PL_POWER_JET,
	//	&PL_ReSponeTime,
	//	&PL_InvincibleTime,
	//	&JT_SCALE[0],
	//	&JT_SCALE[1],
	//	&JT_MOVEMENT_NOMAL,
	//	&JT_MOVEMENT_ACCEL,
	//	&AMOUNT_OF_DECREASE,
	//	&AMOUNT_OF_RECOVERY,
	//	&BA_SCALE,
	//	&BA_SPEED_FLOAT,
	//	&BA_SPEED_SHOT,
	//	&FN_TIME_MOVE,
	//	&FN_TIME_DISPLAY,
	//	&FN_TIME_ALPHA
	//);
}