//
// DontDestroyOnLoad.h
//

#pragma once

#define DontDestroy DontDestroyOnLoad::GetInstance()

// Include Files.
#include "_Classes/_GameModes/GameModes.h"

enum CHARATYPE { TYPE_PLAYER, TYPE_COM };

class DontDestroyOnLoad final
{
private:
	DontDestroyOnLoad() = default;

public:
	~DontDestroyOnLoad() = default;

	DontDestroyOnLoad(DontDestroyOnLoad&&) = default;
	DontDestroyOnLoad& operator= (DontDestroyOnLoad&&) = default;

	DontDestroyOnLoad(DontDestroyOnLoad const&) = delete;
	DontDestroyOnLoad& operator= (DontDestroyOnLoad const&) = delete;

	static DontDestroyOnLoad* GetInstance()
	{
		static DontDestroyOnLoad instance;
		return &instance;
	}

public:
	enum CHARATYPE { TYPE_PLAYER, TYPE_COM };

	GameModes GameMode_;
	CHARATYPE charaType_[4];
	int NowScene_;
	int ChoseColor_[4];
	int TeamID[4];
	int Score_[4];
	bool Survivor_[4];
};
