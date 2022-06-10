/**
 * @file CharaStrategy.h
 * @brief プレイヤーの操作スタイル基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/_ActMove/ActMove.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/_ActThrasher/ActThrasher.h"
#include "_Classes/_CellList/_Object/_Player/_BehaviorTree/_ActShot/ActShot.h"

/**
* @enum OPERATE_TYPE
* プレイヤーの操作方法
*/
enum OPERATE_TYPE { MANUAL, COMPUTER, NONE_OPERATE_TYPE };

//前方宣言
class ObjPlayer;

class CharaStrategy {
public:
	CharaStrategy() : rotate_x_(0.0f) { actList_ = { new ActThrasher(), new ActMove(), new ActShot() }; prevForward_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f); }
	virtual ~CharaStrategy() {}

	virtual void Initialize(int id, ObjPlayer* player) = 0;
	virtual void LoadAssets() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void UIRender() { for (ActionBase* act : actList_) act->UIRender(); }

	/**
	* @brief X軸の角度を返す
	* @return X軸の角度
	*/
	inline float GetRotateX() const { return rotate_x_; }

protected:
	/**
	* @brief なめらかに回転させる
	* @param deltaTime フレームごとの経過時間
	* @param inputDirection 入力方向
	* @return X軸の角度
	*/
	virtual float SeekRotateX(const float deltaTime, DirectX::XMFLOAT2 inputDirection) {
		DirectX::XMFLOAT3 _direction;
		_direction.x = inputDirection.x * std::sqrtf(1.0f - 0.5f * inputDirection.x * inputDirection.y);
		_direction.y = inputDirection.y * std::sqrtf(1.0f - 0.5f * inputDirection.x * inputDirection.y);
		_direction.z = 0;

		prevForward_ = Vector3::Lerp(prevForward_, _direction, deltaTime * 1.0f);
		return atan2f(prevForward_.y, prevForward_.x);
	}

	//! プレイヤー自身
	ObjPlayer* player_;

	//! 行動パターンのリスト
	std::vector<ActionBase*> actList_;
	
	//! 移動方向の補正値
	DirectX::SimpleMath::Vector3 prevForward_;
	
	//! X軸の角度
	float rotate_x_;
};