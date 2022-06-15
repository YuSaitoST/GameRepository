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

class ObjBall final : public ObjectBase {
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

	void WasCaught(const int ownerID, DirectX::XMFLOAT2* handPos);
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
	void SetPhysicsPosition(Vector3 position) {
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

	const float POS_Z_AT_GOAL = 1000.0f;

	XMFLOAT2*	ownerHandPos_;	//! 持ち主の手元の座標
	BallState*	state_;			//! ボールの状態
	COLOR_TYPE	colorType_;		//! 現在の色の状態

	float	pos_z_;				//! Z座標
	int		id_owner_;			//! 持ち主のID
	bool	isInPlayerHands_;	//! プレイヤーの手元にあるか
	bool	isBreak_;			//! 破壊されたか
};