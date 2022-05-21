/**
 * @file Gauge.h
 * @brief スラスターのゲージクラス
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
#include "_Classes/_MainCamera/MainCamera.h"

class Gauge {
public:
	Gauge();
	virtual ~Gauge() = default;

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, bool usedThrasher);
	void Render();

	/**
	* @brief 座標設定
	* @param position 座標
	*/
	void SetPosition(DirectX::XMFLOAT3 position) { position_ = position; };

	/**
	* @brief 現在の値を返す
	* @return 現在の値
	*/
	float GetProportion() const { return proportion_; };

private:
	/**
	* @ brief ゲージ使用
	* @ param deltaTime フレームごとの経過時間
	*/
	void IsDecrease(float& num, float speed, float min) { num = std::max(min, num - speed); }

	/**
	* @ brief ゲージ回復
	* @ param deltaTime フレームごとの経過時間
	*/
	void IsRecovery(float& num, float speed, float max) { num = std::min(num + speed, max); }

	const int	RECT_Y		= 15;
	const float	MAX_GAUGE	= 71;
	const float GtoO		= 0.5f;
	const float OtoR		= 0.2f;
	const DirectX::XMFLOAT3 DISPLAY_POSITION = DirectX::XMFLOAT3(-35.0f, -60.0f, 0.0f);

	/**
	* @enum GAUGECOLOR
	* ゲージの段階色
	*/
	enum GAUGECOLOR {
		GREEN, ORANGE, RED
	} color_;

	//! ゲージ画像(左側)
	DX9::SPRITE sp_gauge_L_[3];

	//! ゲージ画像(右側)
	DX9::SPRITE sp_gauge_R_[3];
	
	//! ゲージ画像(フレーム)
	DX9::SPRITE sp_flame_;

	//! 座標
	DirectX::SimpleMath::Vector3 position_;

	//! 使用時の速度
	float movement_decrease_;
	
	//! 回復時の速度
	float movement_recovery_;

	//! 現在のゲージの値(0.0f～1.0f)
	float proportion_;

	//! ゲージのサイズを元としたゲージの値
	float gauge_;

	//! ゲージの表示幅
	float gauge_rect_x_;
};