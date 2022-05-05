#pragma once

enum GAMEMODE { DODGE_BALL_NOMAL, HAND_BALL, DODGE_BALL_2ON2, BILLIARDS, NONE_GAMEMODE };

class GameModes {
public:
	GameModes() : GameMode_(NONE_GAMEMODE) {}
	virtual ~GameModes() {}

	inline void SelectMode(GAMEMODE gameMode) { GameMode_ = gameMode; }
	inline bool isSINGLES_GAME		() const { return !isDODGEBALL_2ON2	();							}
	inline bool isGAMES_WITH_GOALS	() const { return isHANDBALL		() || isBILLIARDS();		}
	inline bool isDODGEBALL			() const { return isDODGEBALL_NOMAL	() || isDODGEBALL_2ON2();	}
	inline bool isDODGEBALL_NOMAL	() const { return GameMode_ == DODGE_BALL_NOMAL;				}
	inline bool isDODGEBALL_2ON2	() const { return GameMode_ == DODGE_BALL_2ON2;					}
	inline bool isHANDBALL			() const { return GameMode_ == HAND_BALL;						}
	inline bool isBILLIARDS			() const { return GameMode_ == BILLIARDS;						}
	inline GAMEMODE SelectionMode	() const { return GameMode_;									}

private:
	GAMEMODE GameMode_;
};