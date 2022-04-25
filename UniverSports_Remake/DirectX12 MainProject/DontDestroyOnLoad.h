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
	enum GAMEMODE { DODGE_BALL_NOMAL, DODGE_BALL_2ON2, HAND_BALL, BILLIARDS };

	inline bool isDODGEBALL			() const { return isDODGEBALL_NOMAL() || isDODGEBALL_2ON2(); }
	inline bool isDODGEBALL_NOMAL	() const { return GameMode_ == DODGE_BALL_NOMAL; }
	inline bool isDODGEBALL_2ON2	() const { return GameMode_ == DODGE_BALL_2ON2;  }
	inline bool isHANDBALL			() const { return GameMode_ == HAND_BALL;		 }
	inline bool isBILLIARDS			() const { return GameMode_ == BILLIARDS;		 }

	int NowScene_;
	int GameMode_;
	int ChoseColor_[4];
	int Score_[4];
	int winnerID_;
	int winnerTeamID_[2];
	bool Survivor_[4];
};
