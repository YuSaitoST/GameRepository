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

	/**
	* @brief モデル生成
	* @param fileName ファイル名
	*/
	void CreateModel(std::wstring fileName) {
		model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, fileName.c_str());
		model_->SetScale(0.018f);
		model_->SetMaterial(GetNomMaterial());
	}

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

	void AsjustmentForward();

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

private:
	void Playing(const float deltaTime);
	void Beaten(const float deltaTime);

	void SetTransforms(const Vector2 pos, const Vector2 rotate);
	void AnimReset();
	void AnimSet(MOTION motion, float deltaTime);

	/**
	* @brief 現状に合ったアニメーションを返す
	* @return アニメーションの番号
	*/
	MOTION AnimChange();

	const SimpleMath::Vector2 POS_HAND = { -2.75f, -3.0f };

	//! 残機
	MyLife*				life_;
	
	//! チームID
	TeamID*				teamID_;
	
	//! リスポーンタイマー
	CountTimer*			ti_respone_;
	
	//! ダウン時エフェクト
	EffDown*			eff_down_;
	
	//! 行動
	CharaStrategy*		strategy_;
	
	//" バリア
	Barrier*			barrier_;
	
	//! モデル
	DX9::SKINNEDMODEL	model_;
	
	//! ボールの所持状態
	bool				hasBall_;
	
	//! やられ状態
	bool				isDown_;
	
	//! 所持しているボールのID
	int					myBallID_;
};