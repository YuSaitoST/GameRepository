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
#include "_Classes/_SoundPlayer/SoundPlayer.h"
#include "_Strategy/CharaStrategy.h"
#include "_Strategy/_ManualChara/ManualChara.h"
#include "_Strategy/_ComputerChara/ComputerChara.h"
#include "_Barrier/Barrier.h"
#include "_EffDown/EffDown.h"

//前方宣言
class BallsInstructor;
class PlayersInstructor;

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

	void SetInstructor(BallsInstructor* blInstructor, PlayersInstructor* plInstructor) { ballsInstructor_ = blInstructor; playersInstructor_ = plInstructor; }

	void CreateModel(std::wstring fileName);

	/**
	* @brief モデルの変更
	*/
	void ReDecision(const int plID, const std::wstring fileName) {
		CreateModel(fileName);
		pos_ = XMFLOAT2(GAME_CONST.S_POS[plID].x, GAME_CONST.S_POS[plID].y);
		rotate_ = XMFLOAT2(0.0f, GAME_CONST.Player_FacingRight);
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

	///**
	//* @brief 手元の座標を返す
	//* @return 手元の座標のアドレス
	//*/
	//XMFLOAT2* Get_HandPos() { return &handPos_; }

	/**
	* @brief 所持しているボールのIDを返す
	* @return 所持しているボールのID
	*/
	int MyBallID() const { return myBallID_; }

	/**
	* @brief ボールインストラクターを返す
	* @return ボールインストラクター
	*/
	BallsInstructor* GetBallsInstructor() const { return ballsInstructor_; }

	/**
	* @brief プレイヤーインストラクターを返す
	* @return プレイヤーインストラクター
	*/
	PlayersInstructor* GetPlayersInstructor() const { return playersInstructor_; }

	/**
	* @brief ターゲットプレイヤーを変えす
	* @return ターゲットプレイヤー
	*/
	ObjectBase* GetTargetPlayer() const { return targetPlayer_; }

private:
	void Playing(const float deltaTime);
	void Beaten(const float deltaTime);

	void CalculationHandPos();
	void SetTransforms(XMFLOAT2 pos, XMFLOAT2 rotate);
	void AnimReset();
	void AnimSet(MOTION motion, float deltaTime);
	void SertchTarget();

	/**
	* @brief 現状に合ったアニメーションを返す
	* @return アニメーションの番号
	*/
	MOTION AnimChange();

	const SimpleMath::Vector2 POS_HAND = { -2.75f, -3.0f };

	std::unique_ptr<MyLife>			life_;			//! 残機
	std::unique_ptr<CountTimer>		ti_respone_;	//! リスポーンタイマー
	std::unique_ptr<EffDown>		eff_down_;		//! ダウン時エフェクト
	std::unique_ptr<Barrier>		barrier_;		//! バリア
	std::unique_ptr<SoundPlayer>	se_shot_;		//! ショット時SE
	std::unique_ptr<SoundPlayer>	se_defeat_;		//! 爆破時SE
	
	CharaStrategy*		strategy_;			//! 行動
	ObjectBase*			targetPlayer_;			//! ターゲットのオブジェクト
	BallsInstructor*	ballsInstructor_;	//! ボールインストラクター
	PlayersInstructor*	playersInstructor_;	//! プレイヤーインストラクター

	XMFLOAT2			handPos_;			//! 手元の座標

	DX9::SKINNEDMODEL	model_;				//! モデル

	bool				hasBall_;			//! ボールの所持状態
	bool				isDown_;			//! やられ状態
	int					myBallID_;			//! 所持しているボールのID
};