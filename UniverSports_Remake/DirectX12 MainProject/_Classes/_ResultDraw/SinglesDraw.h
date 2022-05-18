/**
 * @file SinglesDraw.h
 * @brief シングルスモード時の描画クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "DrawingByMode.h"

class SinglesDraw final : public DrawingByMode {
public:
	SinglesDraw() {}
	virtual ~SinglesDraw() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual void Render() override;
};