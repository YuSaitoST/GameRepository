//
// LobbyScene.h
//

#pragma once

#include "Scene.h"
#include "Base/DX12Effekseer.h"
#include <btBulletDynamicsCommon.h>

#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_MoviePlayer/MoviePlayer.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"

#include "_Classes/_MainCamera/MainCamera.h"
#include "_Classes/_MainLight/MainLight.h"

#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"

#include "_Classes/_UI/_CharaSelect/CharaSelect.h"
#include "_Classes/_UI/_OriTimer/OriTimer.h"

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
	static void ChangeStrategy(const int plIndex);

private:
	void Render_String();
	bool AllDecision();

private:
	static const int PLAYER = 4;
	const int VIEW_X = 288;
	const int VIEW_Y = 98;
	const int VIEW_W = 720;
	const int VIEW_H = 403;

	static ObjPlayer* player_[PLAYER];

	DX12::DESCRIPTORHEAP				descriptorHeap_;
	DX12::SPRITEBATCH					spriteBatch_;
	DX12::HGPUDESCRIPTOR				dx9GpuDescriptor_;

	DX9::SPRITEFONT						font_count_;
	DX9::SPRITEFONT						font_message_;

	DX9::SPRITE							sp_bg;
	DX9::SPRITE							sp_right;
	DX9::SPRITE							sp_left;
	DX9::SPRITE							sp_decisions[PLAYER];
	DX9::SPRITE							sp_entry;
	DX9::SPRITE							sp_playerIcon[PLAYER];
	DX9::SPRITE							sp_teamCol_[PLAYER / 2];

	btDynamicsWorld*					physics_world_;
	btDefaultCollisionConfiguration*	collision_config_;
	btCollisionDispatcher*				collision_dispatcher_;
	btBroadphaseInterface*				broadphase_;
	btConstraintSolver*					solver_;

	MoviePlayer*						bg_movie_;
	SoundPlayer*						bgm_;

	CharaSelect*						charaSelect_[PLAYER];
	OriTimer*							timer_goNext_;

	bool								allSet_;
};