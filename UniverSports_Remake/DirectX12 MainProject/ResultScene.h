//
// TemplateScene.h
//

#pragma once

#include "Scene.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"
#include "_Classes/_MoviePlayer/MoviePlayer.h"
#include "_Classes/_UI/_BlackOut/BlackOut.h"
#include "_Classes/_ResultDraw/DrawingByMode.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class ResultScene final : public Scene {
public:
	ResultScene();
	virtual ~ResultScene() { Terminate(); }

	ResultScene(ResultScene&&) = default;
	ResultScene& operator= (ResultScene&&) = default;

	ResultScene(ResultScene const&) = delete;
	ResultScene& operator= (ResultScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;


private:
	const float					SPEED_FADE[3] = { 127.5f, 510.0f, 0.0f };  // シーン移行のフェード速度(2s, 0.5s、0.0s)

	DX12::DESCRIPTORHEAP		descriptorHeap_;
	DX12::SPRITEBATCH			spriteBatch_;
	DX12::HGPUDESCRIPTOR		dx9GpuDescriptor_;

	DX9::SPRITE					sp_bg_tile_;
	DX9::SPRITE					sp_texWin_;
	DX9::SPRITE					sp_texPressB_;
	DX9::SPRITE					sp_texCrushing_;

	SoundPlayer*				bgm_;
	SoundPlayer*				se_decision_;
	MoviePlayer*				bg_movie_;
	BlackOut*					blackOut_;

	DrawingByMode*				drawingByMode_;

	bool						goNext_;
};