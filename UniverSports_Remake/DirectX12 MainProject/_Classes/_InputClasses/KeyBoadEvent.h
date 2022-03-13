#pragma once

#include "KeyBoadBase.h"

class KeyBoadEvent final : public KeyBoadBase {
public:
	KeyBoadEvent() {};
	virtual ~KeyBoadEvent() {};

	virtual void Accepts() override;
};