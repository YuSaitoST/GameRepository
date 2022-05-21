/**
 * @file ActionBase.h
 * @brief プレイヤーの行動基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

/**
* @enum BEHAVIOR
* 行動パターン
*/
enum BEHAVIOR { IS_MOVE, IS_SHOT, IS_ACCEL, IS_NONE };

//前方宣言
class ObjPlayer;

class ActionBase {
public:
	ActionBase() {};
	virtual ~ActionBase() {};

	virtual void Initialize(int id) = 0;
	virtual void LoadAssets() = 0;
	virtual void Update(const float deltaTime, SimpleMath::Vector2 direction, ObjPlayer& player) = 0;  // 行動内容(Manual用)
	virtual void Update(const float deltaTime, ObjPlayer& player) = 0;  // 行動内容(Computer用)
	virtual void UIRender() = 0;

	virtual bool Think(ObjPlayer& player) = 0;  // 行動条件を考慮する

	/**
	* @brief 正面方向を返す
	* @return 正面方向
	*/
	SimpleMath::Vector2 GetDirection() { return direction_; };

protected:
	//! 正面ベクトル
	SimpleMath::Vector2 direction_;
};