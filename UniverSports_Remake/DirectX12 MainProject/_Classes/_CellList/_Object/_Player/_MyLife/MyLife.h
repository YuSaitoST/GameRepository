#pragma once

#include <algorithm>

class MyLife {
public:
	MyLife(int life) : life_(life) {}
	virtual ~MyLife() {}

	void TakeDamage() { life_ = std::max(0, life_ - 1); }
	int NowLifePoint() const { return life_; }

private:
	int life_;
};