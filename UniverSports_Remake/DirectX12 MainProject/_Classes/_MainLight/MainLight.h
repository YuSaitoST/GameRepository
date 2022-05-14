/**
 * @file MainLight.h
 * @brief ライトクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class MainLight {
public:
	MainLight() {}
	virtual ~MainLight() {};

	void Register();
};