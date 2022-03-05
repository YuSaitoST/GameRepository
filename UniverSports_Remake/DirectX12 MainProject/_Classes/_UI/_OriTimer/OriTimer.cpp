#include "OriTimer.h"

OriTimer::OriTimer(float countTime) {
	max_		= countTime;
	time_		= max_;
}

void OriTimer::Update(const float deltaTime) {
	time_ = std::max(0.0f, time_ - deltaTime);
}