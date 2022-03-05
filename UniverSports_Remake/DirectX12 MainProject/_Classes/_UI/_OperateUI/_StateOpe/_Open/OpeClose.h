#pragma once

#include "_Classes/_UI/_OperateUI/_StateOpe/StateOpeBase.h"

class OpeClose : public OP_StateBase {
public:
	OpeClose() = default;
	virtual ~OpeClose() = default;

	virtual void Initialize();
	virtual void Update(const float deltaTime, OperateUI* operate);
};