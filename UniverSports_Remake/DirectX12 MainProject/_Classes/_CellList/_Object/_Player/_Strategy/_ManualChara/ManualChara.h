#pragma once

#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_CellList/_Object/_Player/_Strategy/CharaStrategy.h"

class ManualChara final : public CharaStrategy {
public:
	ManualChara() {};
	virtual ~ManualChara() {};

	virtual void Initialize(int id, ObjPlayer* player);
	virtual void LoadAssets();
	virtual void Update(const float deltaTime);

	virtual void SeekRotate(const float deltaTime, int index);
};