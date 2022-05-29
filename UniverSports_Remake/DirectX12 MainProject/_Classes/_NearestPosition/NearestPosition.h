/**
 * @file NearestPosition.h
 * @brief 一番近い物体を調べる処理
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"

namespace PosCheck {
	int GetNearestObjectID(std::vector<DirectX::SimpleMath::Vector2*> positionList, DirectX::SimpleMath::Vector2 position);

}  //namespace Position