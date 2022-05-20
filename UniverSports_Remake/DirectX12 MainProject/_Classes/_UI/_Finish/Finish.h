/**
 * @file Finish.h
 * @brief 終了時の演出クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class Finish {
public:
	Finish();
	virtual ~Finish() = default;

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

	/**
	* @brief アニメーションの終了状態を返す
	* @return アニメーションの終了状態
	*/
	bool isAnimationFine() const { return (alpha_ == 0.0f); };

private:
	const float MOVEMENT = 640.0f;

	//! 終了画像
	DX9::SPRITE sprite_;
	
	//! 座標
	DirectX::XMFLOAT3 position_;
	
	//! アニメーションの移動量
	float movement_move_;
	
	//! α値の変化量
	float movement_alpha_;
	
	//! 表示時間
	float time_display_;
	
	//! α値
	float alpha_;
};