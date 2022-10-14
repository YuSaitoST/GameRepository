/**
 * @file EffDown.h
 * @brief ダウン時のエフェクトクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <algorithm>
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/EffectBase.h"

class EffDown final : public EffectBase {
public:
	EffDown() : EffectBase() {};
	virtual ~EffDown() {};
};