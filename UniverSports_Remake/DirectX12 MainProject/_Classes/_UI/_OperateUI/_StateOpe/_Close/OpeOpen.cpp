#include "OpeOpen.h"
#include "_Classes/_UI/_OperateUI/OperateUI.h"

void OpeOpen::Initialize() {
	pos_ope_pad_ = SimpleMath::Vector3(0.0f, 0.0f, -98.0f);
	pos_ope_key_ = SimpleMath::Vector3(0.0f, 0.0f, -99.0f);
}

void OpeOpen::Update(const float deltaTime, OperateUI* operate) {
	pos_ope_pad_.x = std::min(pos_ope_pad_.x + SPEED_X * deltaTime, 0.0f);

	if (pos_ope_pad_.x == 0.0f && operate->isState() == 2)
		pos_ope_key_.x = std::min(pos_ope_key_.x + SPEED_X * deltaTime, 0.0f);
}