/**
 * @file ObjPlayer.h
 * @brief プレイヤークラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/ObjectBase.h"
#include "_Classes/_CellList/_Object/_Player/_MyLife/MyLife.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_CellList/_TeamID/TeamID.h"
#include "_Strategy/CharaStrategy.h"
#include "_Strategy/_ManualChara/ManualChara.h"
#include "_Strategy/_ComputerChara/ComputerChara.h"
#include "_Barrier/Barrier.h"
#include "_EffDown/EffDown.h"

//前方宣言
class BallsInstructor;

class ObjPlayer final : public ObjectBase {
private:
	/**
	* @enum MOTION
	* プレイヤーモデルに登録されているアニメーション
	*/
	enum MOTION {
		STAND,
		STAND_TO_CATCH,
		HAND,
		HAND_TO_READY,
		READY,
		IS_SHOT
	};

public:
	ObjPlayer();
	ObjPlayer(OPERATE_TYPE strategy, Vector3 pos, float r);
	virtual ~ObjPlayer();

	virtual void Initialize(const int id);
	virtual void LoadAssets(std::wstring file_name);
	virtual void LoadAssets(DX9::MODEL& model) {}
	virtual void Update(const float deltaTime);
	virtual void Render();
	virtual void Render(DX9::MODEL& model) {}
	virtual void UIRender();
	void AlphaRender();

	virtual void HitAction(ObjectBase* hitObject);

	void SetInstructor(BallsInstructor* instructor) { instructor_ = instructor; }

	void CreateModel(std::wstring fileName);

	/**
	* @brief モデルの変更
	*/
	void ReDecision(const int plID, const std::wstring fileName) {
		CreateModel(fileName);
		pos_ = Vector2(GAME_CONST.S_POS[plID].x, GAME_CONST.S_POS[plID].y);
		rotate_ = Vector2(0.0f, GAME_CONST.Player_FacingRight);
		SetTransforms(pos_, rotate_);
	}

	/**
	* @brief 操作タイプの変更
	*/
	void ChangeStrategy() {
		strategy_ = new ComputerChara();
		strategy_->Initialize(id_my_, this);
	}

	/**
	* @brief 移動処理
	*/
	void Moving(Vector3 power) { physics_->Moving(power); };

	void Shoting(const int ballID);
	void CautchedBall(const int ballID);

	/**
	* @brief 剛体オブジェクトの中心座標を取得する
	*/
	void AssignPosition() { pos_ = physics_->GetCenterOfMassPosition(); }

	/**
	* @brief 残機数を返す
	* @return 残機数
	*/
	int myLife() const { return life_->NowLifePoint(); }
	
	/**
	* @brief ボールの所持状態を返す
	* @return ボールの所持状態
	*/
	bool HasBall() const { return hasBall_; }
	Vector2 Get_HandPos();

	/**
	* @brief 所持しているボールのIDを返す
	* @return 所持しているボールのID
	*/
	int MyBallID() const { return myBallID_; }

	/**
	* @brief インストラクターを返す
	* @return インストラクター
	*/
	BallsInstructor* GetInstructor() const { return instructor_; }

private:
	void Playing(const float deltaTime);
	void Beaten(const float deltaTime);

	void SetTransforms(XMFLOAT2 pos, XMFLOAT2 rotate);
	void AnimReset();
	void AnimSet(MOTION motion, float deltaTime);

	/**
	* @brief 現状に合ったアニメーションを返す
	* @return アニメーションの番号
	*/
	MOTION AnimChange();

	const SimpleMath::Vector2 POS_HAND = { -2.75f, -3.0f };

	std::unique_ptr<MyLife>				life_;			//! 残機
	std::unique_ptr<TeamID>				teamID_;		//! チームID
	std::unique_ptr<CountTimer>			ti_respone_;	//! リスポーンタイマー
	std::unique_ptr<EffDown>			eff_down_;		//! ダウン時エフェクト
	std::unique_ptr<Barrier>			barrier_;		//! バリア
	
	CharaStrategy*		strategy_;		//! 行動
	BallsInstructor*	instructor_;	//! ボールインストラクター

	DX9::SKINNEDMODEL	model_;			//! モデル

	bool				hasBall_;		//! ボールの所持状態
	bool				isDown_;		//! やられ状態
	int					myBallID_;		//! 所持しているボールのID
};