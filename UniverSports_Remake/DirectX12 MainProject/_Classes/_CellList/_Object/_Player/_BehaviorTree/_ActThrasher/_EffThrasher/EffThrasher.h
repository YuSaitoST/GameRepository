#pragma once

#include <algorithm>
#include "_Classes/_InputClasses/InputChecker.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/EffectBase.h"

class EffThrasher final : public EffectBase {
public:
	EffThrasher();
	virtual ~EffThrasher() {};

	void Update(const float deltaTime, float rotate_x, Vector3 position, Vector3 direction);

	bool usedThrasher_;

private:
	OriTimer* timer_roop_;
};