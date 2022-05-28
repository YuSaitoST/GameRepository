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
	//void Clamp(DirectX::SimpleMath::Vector2& position);
	void ClampLoop(DirectX::SimpleMath::Vector2& position);
	bool IsOut(DirectX::SimpleMath::Vector2 position, float raidus);

	//! X座標の最大値
	const float SIDE_X = 32.0f;

	//! Y座標の最大値
	const float SIDE_Y = 18.0f;
	
	//	//! X座標の最大値
	//const float SIDE_X = 64.0f;

	////! Y座標の最大値
	//const float SIDE_Y = 36.0f;

	//! X座標の中央値
	const float CENTER_X = SIDE_X * 0.5f;
	
	//! Y座標の中央値
	const float CENTER_Y = SIDE_Y * 0.5f;

}  //namespace FIELD