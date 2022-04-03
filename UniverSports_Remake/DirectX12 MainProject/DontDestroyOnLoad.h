//
// DontDestroyOnLoad.h
//

#pragma once

#define DontDestroy DontDestroyOnLoad::GetInstance()

// Include Files.

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
	enum GAMEMODE {
		DODGE_BALL_NOMAL,
		DODGE_BALL_2ON2,
		HAND_BALL,
		BILLIARDS
	};

	int GameMode_;
	int ChoseColor_[4];
	int Score_[4];
	int winnerID_;
	int winnerTeamID_[2];
};
