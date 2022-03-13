#pragma once

#include "GamePadBase.h"

class GamePadEvent final : public GamePadBase {
public:
	GamePadEvent() {}
	virtual ~GamePadEvent() {}

	virtual void Accepts(int index) override;
};