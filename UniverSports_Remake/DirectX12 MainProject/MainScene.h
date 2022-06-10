//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include "DontDestroyOnLoad.h"
#include "Base/DX12Effekseer.h"
#include <btBulletDynamicsCommon.h>
#include "_Classes/_ConstStrages/ConstStorages.h"
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

	btDefaultCollisionConfiguration*	collision_config_;	//! 衝突検出方法(デフォルト)
	std::shared_ptr<btDynamicsWorld>	physics_world_;

	std::unique_ptr<SoundPlayer>		bgm_;
	std::unique_ptr<GameField>			field_;
	std::unique_ptr<GameController>		gameController_;
	std::unique_ptr<ObjectManager>		m_object_;
};