/**
 * @file BallState.h
 * @brief ボールの状態基底クラス
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
* @enum B_STATE
* ボールの状態
*/
enum class B_STATE { STANDBY, FLOATING, CAUTCH, SHOT, GOAL, NONE_STATE };

//前方宣言
class ObjBall;

class BallState {
public:
	BallState() : myState_(B_STATE::NONE_STATE) {}
	virtual ~BallState() {}

	virtual void Initialize() = 0;
	virtual void Update(ObjBall* ball) = 0;
	
	/**
	* @brief 状態を返す
	* @return 状態
	*/
	inline B_STATE GetMyState () const { return myState_; }

protected:
	SimpleMath::Vector2 position_;	//! 座標
	B_STATE myState_;				//! 状態
};