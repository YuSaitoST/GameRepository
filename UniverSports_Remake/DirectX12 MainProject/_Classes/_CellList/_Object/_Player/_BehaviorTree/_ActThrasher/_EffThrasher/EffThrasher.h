/**
 * @file EffThrasher.h
 * @brief スラスターエフェクトクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <algorithm>
#include "_Classes/_InputManager/UseKeyChecker.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/EffectBase.h"

class EffThrasher final : public EffectBase {
public:
	EffThrasher();
	virtual ~EffThrasher() {};
	
	void Update(const float deltaTime, float rotate_x, Vector3 position, Vector3 direction, float proportion);

	//! 加速使用
	bool usedThrasher_;

private:
	//! スラスターの加速のペース
	std::unique_ptr<CountTimer> timer_roop_;
};