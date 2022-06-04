/**
 * @file ObjBall.h
 * @brief ボールクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/ObjectBase.h"
#include "_State/BallState.h"
#include "_State/_Standby/StStandby.h"
#include "_State/_Float/StFloat.h"
#include "_State/_Cautch/StCautch.h"
#include "_State/_Shot/StShot.h"
#include "_State/_Goal/StGoal.h"

class ObjBall final : public ObjectBase {
private:
	//! プレイヤーのディフューズ色
	const D3DCOLORVALUE P_DIFFUSE[5] = {
		D3DCOLORVALUE(0.0f,0.65f,0.0f,1.0f),	// 緑(PL.1)
		D3DCOLORVALUE(0.65f,0.0f,0.65f,1.0f),	// 紫(PL.2)
		D3DCOLORVALUE(0.65f,0.0f,0.0f,1.0f),	// 赤(PL.3)
		D3DCOLORVALUE(0.0f,0.0f,0.65f,1.0f),	// 青(PL.4)
		D3DCOLORVALUE(0.0f,0.0f,0.0f,0.0f)
	};
	//! アンビエント色
	const D3DCOLORVALUE P_AMBIENT = D3DCOLORVALUE(0.35f, 0.35f, 0.35f, 1.0f);

public:
	/**
	* @enum COLOR_TYPE
	* ボールの色
	*/
	enum COLOR_TYPE { DEFAULT_COLOR, PLAYERS_COLOR, TEAM_COLOR };

public:
	ObjBall();
	ObjBall(Vector3 pos, float r);
	virtual ~ObjBall();

	virtual void Initialize(const int id);
	virtual void LoadAssets(std::wstring file_name) {}
	virtual void LoadAssets(DX9::MODEL& model);
	virtual void Update(const float deltaTime);
	virtual void Render() {}
	virtual void Render(DX9::MODEL& model);
	virtual void UIRender() {}

	virtual void HitAction(ObjectBase* hitObject) {}

	void WasCaught(const int ownerID);
	void WasThrown(Vector2 forward);
	void WasGoaled();
	void WasGuessed();
	void BallBreak();

	/**
	* @brief 色の変更
	* @param colorType 色のタイプ
	*/
	inline void SwitchColor(COLOR_TYPE colorType) { colorType_ = colorType; }

	void SwitchState(BallState* state);

	/**
	* @brief 力を加えて飛ばす処理
	* @param power 加える力
	*/
	void Moving(Vector3 power) { physics_->Moving(power); }
	void Following(float pos_z);
	void AddPower(XMFLOAT3 forward, float speed);
	void AssignPosition() { pos_ = physics_->GetCenterOfMassPosition(); }

	/**
	* @brief 座標と正面ベクトルを設定する
	* @param position 座標
	* @param forward 正面ベクトル
	*/
	void AssignTransform(Vector3 position, Vector2 forward) {
		pos_ = Vector2(position.x, position.y);
		pos_z_ = position.z;
		forward_ = forward;
	}

	/**
	* @brief 剛体オブジェクトに座標を設定する
	* @param position 座標
	*/
	void PhysicsControll(Vector3 position) {
		AssignTransform(position, Vector2::Zero);
		physics_->SetCenterOfMassTransform(Vector3(pos_.x, pos_.y, pos_z_), Vector3::Zero);
	}
	
	/**
	* @brief 持ち主のIDをセットする
	*/
	inline void SetOwnerID(int id_player) { id_owner_ = id_player; }
	
	/**
	* @brief ボールを破壊された状態にする
	*/
	inline void SetBallBreak(bool flag) { isBreak_ = flag; }
	
	/**
	* @brief 持ち主の手元の座標を保存する
	* @param handPos 手元の座標
	*/
	inline void SetOwnerHandPos(XMFLOAT2* handPos) { ownerHandPos_ = handPos; }

	/**
	* @brief 状態フラグを全てリセットする
	*/
	inline void FlagResets() { isInPlayerHands_ = isBreak_ = false; }
	
	/**
	* @brief 持ち主のIDを返す
	* @return 持ち主のID
	*/
	inline int GetOwnerID() const { return id_owner_; }

	/**
	* @brieff Z座標を返す
	* @return Z座標
	*/
	inline float myPosZ() const { return pos_z_; }

	/**
	* @brief 持ち主の手元にあるかを返す
	* @return 持ち主の手元にあればtrue
	*/
	inline bool IsInPlayerHands() const { return isInPlayerHands_; }

	/**
	* @brief 破壊されたかを返す
	* @return 破壊されていればtrue
	*/
	inline bool IsBreaked() const { return isBreak_; }

	/**
	* @brief 現在の状態を返す
	* @return 現在の状態
	*/
	inline B_STATE NowState() const { return state_->GetMyState(); }

private:
	D3DMATERIAL9 ChangeMaterial(COLOR_TYPE colorType);

	//! 持ち主の手元の座標
	XMFLOAT2* ownerHandPos_;

	//! ボールの状態
	BallState* state_;

	//! 待機状態
	StStandby st_standby_;
	
	//! 浮遊状態
	StFloat st_float_;
	
	//! キャッチされている状態
	StCautch st_cautch_;

	//! 投げられた状態
	StShot st_shot_;

	//! ゴールに入った状態
	StGoal st_goal_;

	//! 現在の色の状態
	COLOR_TYPE colorType_;

	//! Z座標
	float pos_z_;

	//! 持ち主のID
	int id_owner_;

	//! プレイヤーの手元にあるか
	bool isInPlayerHands_;

	//! 破壊されたか
	bool isBreak_;
};