//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include "DontDestroyOnLoad.h"
#include "Base/DX12Effekseer.h"
#include <btBulletDynamicsCommon.h>

#include "_Classes/_ConstStrages/ConstStorages.h"

#include "_Classes/_UI/_CharaIcon/IconAnimator.h"
#include "_Classes/_GameField/GameField.h"
#include "_Classes/_GameController/GameController.h"

#include "_Classes/_MainCamera/MainCamera.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"
#include "_Classes/_CellList/ObjectManager.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class MainScene final : public Scene {
public:
	MainScene();
	virtual ~MainScene() { Terminate(); }

	MainScene(MainScene&&) = default;
	MainScene& operator= (MainScene&&) = default;

	MainScene(MainScene const&) = delete;
	MainScene& operator= (MainScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:
	DX12::DESCRIPTORHEAP				descriptorHeap_;
	DX12::SPRITEBATCH					spriteBatch_;
	DX12::HGPUDESCRIPTOR				dx9GpuDescriptor_;

	btDynamicsWorld*					physics_world_;
	btDefaultCollisionConfiguration*	collision_config_;
	btCollisionDispatcher*				collision_dispatcher_;
	btBroadphaseInterface*				broadphase_;
	btConstraintSolver*					solver_;

	SoundPlayer*						bgm_;
	IconAnimator*						icon_animator_;
	GameField*							field_;
	GameController*						gameController_;
	ObjectManager*						m_object_;

private:
	enum POS_Z_2D {
		PLAYER_UI  = -990,  // UI‚Í-90‘ä‚É‚·‚é‚Æ•ª‚©‚è‚â‚·‚¢
		HOLE_FLONT = -980,
		BACKGROUND =  999
	};
};