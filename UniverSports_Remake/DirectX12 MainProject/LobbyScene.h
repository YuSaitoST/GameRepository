//
// LobbyScene.h
//

#pragma once

#include "Scene.h"
#include "Base/DX12Effekseer.h"
#include <btBulletDynamicsCommon.h>

#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_MainCamera/MainCamera.h"
#include "_Classes/_MainLight/MainLight.h"

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
	DX12::DESCRIPTORHEAP	descriptorHeap_;
	DX12::SPRITEBATCH		spriteBatch_;
	DX12::HGPUDESCRIPTOR	dx9GpuDescriptor_;

	btDynamicsWorld* physics_world_;
	btDefaultCollisionConfiguration* collision_config_;
	btCollisionDispatcher* collision_dispatcher_;
	btBroadphaseInterface* broadphase_;
	btConstraintSolver* solver_;

};