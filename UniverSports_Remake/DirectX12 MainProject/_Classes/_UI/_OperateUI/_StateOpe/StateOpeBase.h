#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class OperateUI;

class OP_StateBase {
public:
	OP_StateBase() { pos_ope_key_ = SimpleMath::Vector3::Zero; };
	virtual ~OP_StateBase() = default;

	virtual void Initialize() = 0;
	virtual void Update(const float deltaTime, OperateUI* operate) = 0;

	void SetPosPad(SimpleMath::Vector3 position) { pos_ope_pad_ = position; };
	void SetPosKey(SimpleMath::Vector3 position) { pos_ope_key_ = position; };

	SimpleMath::Vector3 myPosPad() const { return pos_ope_pad_; };
	SimpleMath::Vector3 myPosKey() const { return pos_ope_key_; };

protected:
	const float SPEED_X = 875.0f;
	SimpleMath::Vector3 pos_ope_pad_;
	SimpleMath::Vector3 pos_ope_key_;
};