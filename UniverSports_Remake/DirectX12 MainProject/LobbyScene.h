//
// LobbyScene.h
//

#pragma once

#include "Scene.h"
#include <random>
#include <array>
#include <btBulletDynamicsCommon.h>
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_MoviePlayer/MoviePlayer.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"
#include "_Classes/_MainCamera/MainCamera.h"
#include "_Classes/_MainLight/MainLight.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_UI/_CharaSelect/CharaSelect.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"
#include "_Classes/_UI/_BlackOut/BlackOut.h"
#include "_Classes/_UI/_UserInputRender/UserInputRender.h"
#include "_Classes/_UI/_TeamColor/TeamColor.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class LobbyScene final : public Scene {
public:
	LobbyScene();
	virtual ~LobbyScene() { Terminate(); }

	LobbyScene(LobbyScene&&) = default;
	LobbyScene& operator= (LobbyScene&&) = default;

	LobbyScene(LobbyScene const&) = delete;
	LobbyScene& operator= (LobbyScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

	static void ChangeModel(const int plIndex, const int selectID);

private:
	void Render_String();
	bool AllDecision();

private:
	const float	SPEED_FADE[3]	= { 127.5f, 510.0f, 0.0f };  // シーン移行のフェード速度(2s, 0.5s、0.0s)

	static std::unique_ptr<ObjPlayer>	player_[OBJECT_MAX::PLAYER];

	DX12::DESCRIPTORHEAP				descriptorHeap_;
	DX12::SPRITEBATCH					spriteBatch_;
	DX12::HGPUDESCRIPTOR				dx9GpuDescriptor_;

	DX9::SPRITEFONT						font_count_;
	DX9::SPRITEFONT						font_message_;

	DX9::SPRITE							sp_bg_;
	DX9::SPRITE							sp_hole_;
	DX9::SPRITE							sp_right_;
	DX9::SPRITE							sp_left_;
	DX9::SPRITE							sp_playerIcon_[OBJECT_MAX::PLAYER];

	btDefaultCollisionConfiguration*	collision_config_;					//! 衝突検出方法(デフォルト)
	std::unique_ptr<btDynamicsWorld>	physics_world_;						//! 物理演算ワールド

	std::unique_ptr<MoviePlayer>		bg_movie_;							//! 背景
	std::unique_ptr<SoundPlayer>		bgm_;								//! BGM
	std::unique_ptr<CharaSelect>		charaSelect_[OBJECT_MAX::PLAYER];	//! キャラクター選択
	std::unique_ptr<CountTimer>			timer_goNext_;						//! シーン遷移までのカウントダウン
	std::unique_ptr<BlackOut>			blackOut_;							//! ブラックアウト
	std::unique_ptr<TeamColor>			teamColor_;							//! チームカラー
	std::array<std::unique_ptr<UserInputRender>, 2> userInputRender_;		//! 入力状態の表示

	bool								allSet_;							//! 全プレイヤー選択完了
};