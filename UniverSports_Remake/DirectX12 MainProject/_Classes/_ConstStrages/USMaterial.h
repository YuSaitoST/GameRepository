/**
 * @file USMaterial.h
 * @brief マテリアル用の色
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"

namespace USMaterial {
	//! プレイヤーに合ったディフューズ色
	const D3DCOLORVALUE P_DIFFUSE[5] = {
		D3DCOLORVALUE(0.0f,0.65f,0.0f,1.0f),	// 緑(PL.1)
		D3DCOLORVALUE(0.65f,0.0f,0.65f,1.0f),	// 紫(PL.2)
		D3DCOLORVALUE(0.65f,0.0f,0.0f,1.0f),	// 赤(PL.3)
		D3DCOLORVALUE(0.0f,0.0f,0.65f,1.0f),	// 青(PL.4)
		D3DCOLORVALUE(0.0f,0.0f,0.0f,0.0f)
	};
	//! アンビエント色
	const D3DCOLORVALUE P_AMBIENT = D3DCOLORVALUE(0.35f, 0.35f, 0.35f, 1.0f);

}	//namespace USMaterial