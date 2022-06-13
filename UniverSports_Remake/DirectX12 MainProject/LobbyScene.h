//
// LobbyScene.h
//

#pragma once

#include "Scene.h"
#include <random>
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
	void GiveTeamID(int myID);
	int HowManyValuesIn(const int* list, int size, int findNum);
	bool AllDecision();

private:
	const float			SPEED_FADE[3]	= { 127.5f, 510.0f, 0.0f };  // シーン移行のフェード速度(2s, 0.5s、0.0s)

	static std::unique_ptr<ObjPlayer> player_[OBJECT_MAX::PLAYER];

	std::mt19937						randomEngine_;
	std::uniform_int_distribution<>		newTeamID_;

	DX12::DESCRIPTORHEAP				descriptorHeap_;
	DX12::SPRITEBATCH					spriteBatch_;
	DX12::HGPUDESCRIPTOR				dx9GpuDescriptor_;

	DX9::SPRITEFONT						font_count_;
	DX9::SPRITEFONT						font_message_;

	DX9::SPRITE							sp_bg;
	DX9::SPRITE							sp_right;
	DX9::SPRITE							sp_left;
	DX9::SPRITE							sp_decisions[2];
	DX9::SPRITE							sp_entry;
	DX9::SPRITE							sp_playerIcon[OBJECT_MAX::PLAYER];
	//DX9::SPRITE							sp_teamCol_[OBJECT_MAX::PLAYER / 2];

	btDefaultCollisionConfiguration*	collision_config_;		//! 衝突検出方法(デフォルト)
	std::unique_ptr<btDynamicsWorld>	physics_world_;

	std::unique_ptr<MoviePlayer>		bg_movie_;
	std::unique_ptr<SoundPlayer>		bgm_;

	std::unique_ptr<CharaSelect>		charaSelect_[OBJECT_MAX::PLAYER];
	std::unique_ptr<CountTimer>			timer_goNext_;
	std::unique_ptr<BlackOut>			blackOut_;
	std::unique_ptr<TeamColor>			teamColor_;

	bool								allSet_;
};