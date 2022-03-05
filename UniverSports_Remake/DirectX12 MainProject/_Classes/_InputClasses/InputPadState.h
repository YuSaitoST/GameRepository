#pragma once

#include "InputBasePad.h"

class InputPadState final : public InputBasePad {
public:
	InputPadState() {};
	virtual ~InputPadState() {};

	virtual void Initialize() override;
	virtual void Accepts() override;
};