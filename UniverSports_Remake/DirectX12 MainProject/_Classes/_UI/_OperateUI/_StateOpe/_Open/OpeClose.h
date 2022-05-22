/**
 * @file OpeClose.h
 * @brief 操作説明画像の非表示クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_UI/_OperateUI/_StateOpe/StateOpeBase.h"

class OpeClose : public OP_StateBase {
public:
	OpeClose() {};
	virtual ~OpeClose() {};

	virtual void Initialize() override;
	virtual void Update(const float deltaTime, OperateUI* operate) override;
};