#pragma once

#include "_Classes/_UI/_OperateUI/_StateOpe/StateOpeBase.h"

class OpeOpen : public OP_StateBase {
public:
	OpeOpen() = default;
	virtual ~OpeOpen() = default;

	virtual void Initialize();
	virtual void Update(const float deltaTime, OperateUI* operate);
};