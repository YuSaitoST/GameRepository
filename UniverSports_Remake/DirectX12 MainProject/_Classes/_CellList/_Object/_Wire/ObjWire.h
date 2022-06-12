/**
 * @file ObjWire.h
 * @brief ワイヤークラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/ObjectBase.h"
#include "_Strategy/WireStrategy.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"

// 前方宣言
class BallsInstructor;
class PlayersInstructor;

class ObjWire final : public ObjectBase {
public:
	ObjWire();
	ObjWire(Vector3 pos, float r);
	virtual ~ObjWire() {}

	virtual void Initialize(const int id);
	virtual void LoadAssets(std::wstring file_name);
	virtual void Update(const float deltaTime);

	virtual void HitAction(ObjectBase* hitObject);

	// 空の実装
	virtual void LoadAssets(DX9::MODEL& model) {}
	virtual void Render() {}
	virtual void Render(DX9::MODEL& model) {}
	virtual void UIRender() {}

	/**
	* @brief インストラクターの設定
	* @param blInstructor ボールインストラクター
	* @param plInstructor プレイヤーインストラクター
	*/
	void SetInstructor(BallsInstructor* blInstructor, PlayersInstructor* plInstructor) { ballsInstructor_ = blInstructor; playersInstructor_ = plInstructor; }

private:
	std::vector<int>				hasBallsID_;	//! ゴール内のボールリスト
	std::unique_ptr<WireStrategy>	strategy_;		//! ワイヤーの振る舞い
	std::unique_ptr<SoundPlayer>	se_goal_;		//! ゴール時のSE

	BallsInstructor*	ballsInstructor_;	//! ボールインストラクター
	PlayersInstructor*	playersInstructor_;	//! プレイヤーインストラクター
};