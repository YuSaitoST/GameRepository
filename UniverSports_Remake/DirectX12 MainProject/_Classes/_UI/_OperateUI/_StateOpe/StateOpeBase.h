/**
 * @file StateOpeBase.h
 * @brief 操作説明画像の表示状態の基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class OperateUI;

class OP_StateBase {
public:
	OP_StateBase() { pos_ope_key_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f); };
	virtual ~OP_StateBase() = default;

	virtual void Initialize() = 0;
	virtual void Update(const float deltaTime, OperateUI* operate) = 0;

	void SetPosPad(DirectX::XMFLOAT3 position) { pos_ope_pad_ = position; };
	void SetPosKey(DirectX::XMFLOAT3 position) { pos_ope_key_ = position; };

	DirectX::XMFLOAT3 myPosPad() const { return pos_ope_pad_; };
	DirectX::XMFLOAT3 myPosKey() const { return pos_ope_key_; };

protected:
	const float SPEED_X = 875.0f;
	DirectX::XMFLOAT3 pos_ope_pad_;
	DirectX::XMFLOAT3 pos_ope_key_;
};