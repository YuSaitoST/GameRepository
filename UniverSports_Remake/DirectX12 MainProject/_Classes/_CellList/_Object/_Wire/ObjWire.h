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
class ObjBall;

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

private:
	const SimpleMath::Vector3 SCALE = SimpleMath::Vector3(13.75f, 2.35f, 10.0f);
	const float ROT_TUNING_Z[2] = { 1.1f, -1.1f };
	const float ROT_Z[2] = { 0.415f, -0.415f };

	//! ゴール内のボールリスト
	std::vector<ObjBall*> hasBalls_;

	//! ワイヤーの振る舞い
	std::unique_ptr<WireStrategy> strategy_;

	//! ゴール時のSE
	std::unique_ptr<SoundPlayer> se_goal_;
};