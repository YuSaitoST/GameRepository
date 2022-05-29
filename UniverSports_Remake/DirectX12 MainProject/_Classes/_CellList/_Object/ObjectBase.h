/**
 * @file ObjectBase.h
 * @brief 空間に所属する物体の基底クラス
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
#include "bdCollision.h"
#include "btObject.h"

using namespace DirectX::SimpleMath;

//前方宣言
class Cell;

/**
* @enum OBJ_TYEP
* 物体の種類
*/
enum OBJ_TYPE { PLAYER, BALL, WIRE, NONE_OBJ_ID };

class ObjectBase {
public:
	ObjectBase();
	ObjectBase(OBJ_TYPE kind, COLLI_TYPE collision, Vector3 pos, float r);
	virtual ~ObjectBase();

	virtual void Initialize(const int id) = 0;
	virtual void LoadAssets(std::wstring file_name) = 0;
	virtual void LoadAssets(DX9::MODEL& model) = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Render(DX9::MODEL& model) = 0;
	virtual void UIRender() = 0;

	virtual void HitAction(ObjectBase* hitObject) = 0;

	virtual ObjectBase* GetCollision(ObjectBase* m);

	ObjectBase* GetHitObject();

	/**
	* @brief 通常のマテリアルを返す
	* @return 通常のマテリアル
	*/
	D3DMATERIAL9 GetNomMaterial() {
		D3DMATERIAL9 _mate{};
		_mate.Diffuse = DX9::Colors::Value(0.3f, 0.3f, 0.3f, 1.0f);
		_mate.Ambient = DX9::Colors::Value(0.7f, 0.7f, 0.7f, 1.0f);
		return _mate;
	}

	/**
	* @brief 速度をリセットする
	*/
	void ResetVelocity() { physics_->ResetVelocity(); }

	/**
	* @brief 自分の物体の種類を返す
	* @return 物体の種類
	*/
	OBJ_TYPE myObjectType() { return obj_type_; }

	/**
	* @brief リジッドボディを返す
	* @return リジッドボディ
	*/
	btRigidBody* myRigidbody() { return physics_->Get_RigidBody(); }

	/**
	* @brief 座標を返す
	* @return 座標
	*/
	Vector2& myPosition() { return pos_; }

	/**
	* @brief 回転を返す
	* @return 回転
	*/
	Vector2 myRotate() { return rotate_; };

	/**
	* @brief 正面ベクトルを返す
	* @return 正面ベクトル
	*/
	Vector2& myDirection() { return forward_; }

	/**
	* @brief 半径を返す
	* @return 半径
	*/
	float myRadian() { return r_; }

	/**
	* @brief 自分のIDを返す
	* @return 自分のID
	*/
	int	myObjectID() { return id_my_; };

protected:
	virtual void SetMember(OBJ_TYPE kind, COLLI_TYPE collision, Vector3 pos, float r);
	virtual void SetTransform(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 rotate);
	virtual void UpdateToMorton();

	std::unique_ptr<bdCollision> collision_;//! 当たり判定
	std::unique_ptr<btObject> physics_;		//! 物理演算
	Cell* cp_;				//! 所属空間
	OBJ_TYPE obj_type_;		//! オブジェクトの種類
	Vector2 pos_;			//! 座標
	Vector2 rotate_;		//! 回転
	Vector2 forward_;       //! 正面方向
	float r_;               //! 半径
	int id_my_;			    //! 自分のID
};