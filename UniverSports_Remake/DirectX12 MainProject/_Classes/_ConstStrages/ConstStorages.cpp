#include "ConstStorages.h"

#include <stdio.h>
#include <cstdlib>

void ConstStorageC::Initialize() {

	FILE* _file;

	auto a = _wfopen_s(&_file, L"paraList.csv", L"r");
	if (a != 0)
		std::abort();

	char _dummyLine[512];
	fgets(_dummyLine, 500, _file);

	fscanf_s(_file, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		&LB_GONEXT,
		&PL_SCALE,
		&PL_SPEED_MAX,
		&PL_SPEED_TURN,
		&PL_JET_MAX,
		&PL_POWER_JET,
		&PL_ReSponeTime,
		&PL_InvincibleTime,
		&JT_SCALE[0],
		&JT_SCALE[1],
		&JT_MOVEMENT_NOMAL,
		&JT_MOVEMENT_ACCEL,
		&AMOUNT_OF_DECREASE,
		&AMOUNT_OF_RECOVERY,
		&BA_SCALE,
		&BA_SPEED_FLOAT,
		&BA_SPEED_SHOT,
		&FN_TIME_MOVE,
		&FN_TIME_DISPLAY,
		&FN_TIME_ALPHA
	);

	// DateApps終了後、異常な値が入っていないかチェックする処理を書く（アピールポイントになる）

	fclose(_file);
}