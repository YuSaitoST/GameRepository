#pragma once

#include <algorithm>

class OriTimer {
public:
	OriTimer(float countTime);
	virtual ~OriTimer() = default;

	void Update(const float deltaTime);
	void ResetCountTime() { time_ = max_; };

	float NowTime() const { return time_; };
	bool TimeOut() const { return (time_ <= 0.0f); };

private:
	float				max_;
	float				time_;
};