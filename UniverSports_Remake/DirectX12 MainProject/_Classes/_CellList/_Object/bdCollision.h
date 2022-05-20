/**
 * @file bdCollision.h
 * @brief 当たり判定クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"

using namespace DirectX;

/**
* enum COLLI_TYPE
* 当たり判定の形状
*/
enum COLLI_TYPE{ SPHRER, ORIENTEDBOX, NONE_COLLI_TYPE };

class bdCollision {
public:
	bdCollision(COLLI_TYPE collision) { type_ = collision; }
	virtual ~bdCollision() {}


	/**
	* @brief 座標を設定する
	* @param pos 座標
	*/
	void SetPosition(SimpleMath::Vector3 pos) { (type_ == SPHRER) ? sph_.Center = pos : (type_ == ORIENTEDBOX) ? box_.Center = pos : XMFLOAT3(0.0f, 0.0f, 0.0f); }

	/**
	* @brief 当たり判定の登録(立方体)
	* @param bound 物体のコリジョン
	*/
	void SetColli(BoundingOrientedBox bound) { box_ = bound; }

	/**
	* @brief 当たり判定の登録(球体)
	* @param bound 物体のコリジョン
	*/
	void SetColli(BoundingSphere bound) { sph_ = bound; }

	/**
	* @brief サイズ補正
	* @param scale サイズ
	*/
	void SetColliScale(float scale) { sph_.Radius *= scale; }


	/**
	* @brief コリジョンを返す(立方体)
	* @return コリジョン
	*/
	BoundingOrientedBox GetBoundingBox() const { return box_; }

	/**
	* @brief コリジョンを返す(球体)
	* @return コリジョン
	*/
	BoundingSphere GetBoundingSph() const { return sph_; }
	
private:
	//! 当たり判定の形状
	COLLI_TYPE type_;

	//! 球体のコリジョン
	BoundingSphere sph_;

	//! 立方体のコリジョン
	BoundingOrientedBox box_;
};