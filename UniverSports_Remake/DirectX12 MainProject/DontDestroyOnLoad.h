//
// DontDestroyOnLoad.h
//

#pragma once

#define DontDestroy DontDestroyOnLoad::GetInstance()

// Include Files.
#include "_Classes/_GameModes/GameModes.h"
#include "_Classes/_Survivor/survivor.h"
#include "NextScene.h"

/**
* @enum CHARATYPE
* キャラクターの入力タイプ
*/
enum CHARATYPE { TYPE_PLAYER, TYPE_COM, TYPE_NONE };

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
	GameModes GameMode_;
	Survivor Survivor_;

	CHARATYPE charaType_[4];
	
	NextScene NowScene_;
	int ChoseColor_[4];
	int TeamID[4];
	int Score_[4];
};
