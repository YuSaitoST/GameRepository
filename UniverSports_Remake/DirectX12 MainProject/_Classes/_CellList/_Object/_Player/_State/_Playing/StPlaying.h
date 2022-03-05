#pragma once

#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_CellList/_Object/_Player/_State/CharaState.h"

class StPlaying final : public CharaState {
public:
	StPlaying();
	virtual ~StPlaying();

	virtual void Initialize(int id, ObjPlayer* player);
	virtual void LoadAssets();
	virtual void Update(const float deltaTime);

	virtual float GetRotateX() {
		return 0.0f;
	}

private:
	
};