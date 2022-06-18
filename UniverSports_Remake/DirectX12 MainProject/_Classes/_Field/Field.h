/**
 * @file Field.h
 * @brief 場外に出たかのチェック
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"

namespace FIELD {
	void Clamp(DirectX::SimpleMath::Vector2& position);
	void ClampLoop(DirectX::SimpleMath::Vector2& position);
	bool IsOut(DirectX::SimpleMath::Vector2 position, float raidus);

	//! X方向のサイズ
	const float SIZE_X = 64.0f;

	//! Y方向のサイズ
	const float SIZE_Y = 36.0f;

	//! X座標の中央値
	const float HALF_X = SIZE_X * 0.5f;
	
	//! Y座標の中央値
	const float HALF_Y = SIZE_Y * 0.5f;

}  //namespace FIELD