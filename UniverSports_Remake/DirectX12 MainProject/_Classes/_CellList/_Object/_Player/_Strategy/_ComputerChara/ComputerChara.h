#pragma once

#include "_Classes/_CellList/_Object/_Player/_Strategy/CharaStrategy.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/ActionBase.h"

class ComputerChara final : public CharaStrategy {
public:
	ComputerChara() {};
	virtual ~ComputerChara() {};

	virtual void Initialize(int id, ObjPlayer* player);
	virtual void LoadAssets();
	virtual void Update(const float deltaTime);

	virtual void SeekRotateX(const float deltaTime, int index);
};