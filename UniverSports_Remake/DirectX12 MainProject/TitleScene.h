//
// TemplateScene.h
//

#pragma once

#include "Scene.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"
#include "_Classes/_TitleDisplay/DisplayBase.h"
#include "_Classes/_TitleDisplay/NormalDisplay.h"
#include "_Classes/_TitleDisplay/DemoDisplay.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class TitleScene final : public Scene {
public:
	TitleScene();
	virtual ~TitleScene() { Terminate(); }

	TitleScene(TitleScene&&) = default;
	TitleScene& operator= (TitleScene&&) = default;

	TitleScene(TitleScene const&) = delete;
	TitleScene& operator= (TitleScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:
	void SwitchState(DISPLAYMODE mode);

	DX12::DESCRIPTORHEAP			descriptorHeap_;
	DX12::SPRITEBATCH				spriteBatch_;
	DX12::HGPUDESCRIPTOR			dx9GpuDescriptor_;

	std::unique_ptr<SoundPlayer>	bgm_;

	DisplayBase*					display_;
	NormalDisplay					disp_normal_;
	DemoDisplay						disp_demo_;

	DISPLAYMODE						displayMode_;
};