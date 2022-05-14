#include "CountTimer.h"

CountTimer::CountTimer(float countTime) {
	max_		= countTime;
	time_		= max_;
}

/**
* @brief �X�V
* @param deltaTime �t���[�����[�g�ɑ΂��Ă̈��̎���
*/
void CountTimer::Update(const float deltaTime) {
	time_		= std::max(0.0f, time_ - deltaTime);
}