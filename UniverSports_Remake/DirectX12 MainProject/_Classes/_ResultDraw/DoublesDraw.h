/**
 * @file DoublesDraw.h
 * @brief ダブルスモード時の描画クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "DrawingByMode.h"

class DoublesDraw final : public DrawingByMode {
public:
	DoublesDraw() {}
	virtual ~DoublesDraw() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual void Render() override;
};