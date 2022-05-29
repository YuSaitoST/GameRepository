/**
 * @file Barrier.h
 * @brief バリアクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

class Barrier {
public:
	Barrier();
	virtual ~Barrier() {}

	void LoadAsset(float radius);
	void Update(const float deltaTime);
	void Render();

	/**
	* @brief 座標設定
	* @param position 座標
	*/
	void SetPosition(DirectX::XMFLOAT3 position) { mod_->SetPosition(position); };

	/**
	* @brief バリアを表示させる
	*/
	inline void DisprayOn() { isInvincible_ = true; }

	/**
	* @brief 表示状態を返す
	* @return 表示状態
	*/
	inline bool IsDisplayed() const { return isInvincible_; }

private:
	void SetMaterial();

	//! 表示時間のタイマー
	std::unique_ptr<CountTimer> timer_;

	//! バリアモデル
	DX9::MODEL mod_;

	//! 表示状態
	bool isInvincible_;
};