#pragma once

#include "InputBaseKey.h"

class InputKeyState final : public InputBaseKey {
public:
	InputKeyState() {};
	virtual ~InputKeyState() {};

	virtual void Initialize() override;
	virtual void Accepts() override;
};