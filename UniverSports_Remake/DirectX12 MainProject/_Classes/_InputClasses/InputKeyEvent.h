#pragma once

#include "InputBaseKey.h"

class InputKeyEvent final : public InputBaseKey {
public:
	InputKeyEvent() {};
	virtual ~InputKeyEvent() {};

	virtual void Initialize() override;
	virtual void Accepts() override;
};