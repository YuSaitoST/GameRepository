#pragma once

#include "KeyBoadBase.h"

class KeyBoadState final : public KeyBoadBase {
public:
	KeyBoadState() {};
	virtual ~KeyBoadState() {};

	virtual void Accepts() override;
};