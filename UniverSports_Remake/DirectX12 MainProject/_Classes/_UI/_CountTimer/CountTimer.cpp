#include "CountTimer.h"

CountTimer::CountTimer(float countTime) {
	max_		= countTime;
	time_		= max_;
}

/**
* @brief 更新
* @param deltaTime フレームレートに対しての一定の時間
*/
void CountTimer::Update(const float deltaTime) {
	time_		= std::max(0.0f, time_ - deltaTime);
}