//
// LobbyScene.h
//

#pragma once

#include "Scene.h"
#include "Base/DX12Effekseer.h"
#include <btBulletDynamicsCommon.h>

#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_MoviePlayer/MoviePlayer.h"

#include "_Classes/_MainCamera/MainCamera.h"
#include "_Classes/_MainLight/MainLight.h"

#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"

#include "_Classes/_UI/_CharaSelect/CharaSelect.h"

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

private:
	const int VIEW_X = 288;
	const int VIEW_Y = 98;
	const int VIEW_W = 720;
	const int VIEW_H = 403;

	const SimpleMath::Vector3 ADJUSTMENT[4] = {
		SimpleMath::Vector3(0.0f,0.0f,0.0f),
		SimpleMath::Vector3(0.0f,0.0f,0.0f),
		SimpleMath::Vector3(0.0f,0.0f,0.0f),
		SimpleMath::Vector3(0.0f,0.0f,0.0f)
	};

	DX12::DESCRIPTORHEAP				descriptorHeap_;
	DX12::SPRITEBATCH					spriteBatch_;
	DX12::HGPUDESCRIPTOR				dx9GpuDescriptor_;

	DX9::SPRITE							sp_bg;
	DX9::SPRITE							sp_right;
	DX9::SPRITE							sp_left;
	DX9::SPRITE							sp_decisions[2];
	DX9::SPRITE							sp_entry;
	DX9::SPRITE							sp_playerIcon[4];
	DX9::SPRITE							sp_teamCol_[2];

	DX9::SKINNEDMODEL					mod_player_[4];

	btDynamicsWorld*					physics_world_;
	btDefaultCollisionConfiguration*	collision_config_;
	btCollisionDispatcher*				collision_dispatcher_;
	btBroadphaseInterface*				broadphase_;
	btConstraintSolver*					solver_;

	MoviePlayer*						bg_movie_;

	ObjPlayer*							player_[1];

	CharaSelect*						charaSelect_[4];

};