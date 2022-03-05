#include "OpeClose.h"
#include "_Classes/_UI/_OperateUI/OperateUI.h"

void OpeClose::Initialize() {
	pos_ope_pad_ = SimpleMath::Vector3(-1280.0f, 0.0f, -98.0f);
	pos_ope_key_ = SimpleMath::Vector3(-1280.0f, 0.0f, -99.0f);
}

void OpeClose::Update(const float deltaTime, OperateUI* operate) {
	pos_ope_pad_.x = std::max(pos_ope_pad_.x - SPEED_X * deltaTime, -1280.0f);
	pos_ope_key_.x = std::max(pos_ope_key_.x - SPEED_X * deltaTime, -1280.0f);
}