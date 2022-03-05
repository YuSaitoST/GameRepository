#pragma once

#include "InputBasePad.h"

class InputPadEvent final : public InputBasePad {
public:
	InputPadEvent() {};
	virtual ~InputPadEvent() {};

	virtual void Initialize() override;
	virtual void Accepts() override;
};