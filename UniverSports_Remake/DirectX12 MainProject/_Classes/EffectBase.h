/**
 * @file EffectBase.h
 * @brief エフェクトの基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Base/DX12Effekseer.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

using namespace DirectX;

class EffectBase {
public:
	EffectBase() : effect_(EFFECT()) { SetMember(0.0f); }
	EffectBase(const float time) { SetMember(time); }
	virtual ~EffectBase() {};

	inline void SetMember(const float time) {
		timer_ = new CountTimer(time);
	}

	virtual void Initialize(std::string eff_name) { name_ = eff_name; }
	virtual void LoadAsset(std::wstring file_name) { effect_ = DX12Effect.Create(file_name.c_str(), name_); }

	/**
	* @brief タイマーをリセットする
	*/
	virtual void ResetTime() { timer_->Reset(); }

	/**
	* @brief 座標を調整する
	* @position 座標
	*/
	virtual void Set_Position(SimpleMath::Vector3 position) { DX12Effect.SetPosition(name_, position); }

	/**
	* @brief 回転させる
	* @param rotate 回転
	*/
	virtual void Set_Rotate(SimpleMath::Vector3 rotate) { DX12Effect.SetRotation(name_, rotate); }

	/**
	* @brief サイズ調整
	* @param scale サイズ
	*/
	virtual void Set_Scale(SimpleMath::Vector3 scale) { DX12Effect.SetScale(name_, scale); }

	/**
	* @brief 再生
	*/
	virtual void Play() { DX12Effect.Play(name_); }

	/**
	* @brief 単発再生
	*/
	virtual void PlayOneShot() { DX12Effect.PlayOneShot(name_); }

	/**
	* @brief 停止
	*/
	virtual void Pause() { DX12Effect.Pause(name_); }

	/**
	* @brief 移動
	* @param movement 移動量
	*/
	virtual void Move(SimpleMath::Vector3 movement) { DX12Effect.MoveEffect(name_, movement); }

	/**
	* @brief タイマーの計測
	* @param deltaTime フレームごとの経過時間
	*/
	virtual void TimerCount(const float deltaTime) { timer_->Update(deltaTime); }

	/**
	* @brief タイマーの終了状態を返す
	* @return タイマーの終了状態
	*/
	virtual bool isOver() { return timer_->TimeOut(); }

protected:
	//! エフェクト
	EFFECT		effect_;
	
	//! 再生時間タイマー
	CountTimer*	timer_;
	
	//! エフェクト名
	std::string name_;
};