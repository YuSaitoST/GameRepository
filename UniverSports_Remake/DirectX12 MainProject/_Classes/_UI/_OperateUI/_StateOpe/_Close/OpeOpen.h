/**
 * @file OpeOpen.h
 * @brief 操作説明画像の表示状態クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_UI/_OperateUI/_StateOpe/StateOpeBase.h"

class OpeOpen : public OP_StateBase {
public:
	OpeOpen() {};
	virtual ~OpeOpen() {};

	virtual void Initialize() override;
	virtual void Update(const float deltaTime, OperateUI* operate) override;
};