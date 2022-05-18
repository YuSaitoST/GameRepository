/**
 * @file FieldOutCheck.h
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
	void ClampLoop(DirectX::SimpleMath::Vector2& position);
	bool IsOut(DirectX::SimpleMath::Vector2 position, float raidus);
}  //namespace FIELD