//
// TemplateScene.h
//

#pragma once

#include "Scene.h"
#include "DontDestroyOnLoad.h"

#include "_Classes/_InputClasses/InputChecker.h"

#include "_Classes/_SoundPlayer/SoundPlayer.h"
#include "_Classes/_MoviePlayer/MoviePlayer.h"
#include "_Classes/_DemoPlay/DemoPlay.h"

#include "_Classes/_UI/_OriTimer/OriTimer.h"
#include "_Classes/_UI/_Cursor/Cursor.h"
#include "_Classes/_UI/_SelectArrows/SelectArrows.h"
#include "_Classes/_UI/_Choices/Choices.h"
#include "_Classes/_UI/_SelectText/TextBase.h"
#include "_Classes/_UI/_SelectText/TextUI.h"
#include "_Classes/_UI/_FadeAlpha/FadeAlpha.h"
#include "_Classes/_UI/_OperateUI/OperateUI.h"

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

	void ChooseMode();
	void DefaultRender();

private:
	const std::wstring		UI_TEXT_FILE_NAME[2][4] = {
	{
		L"_Images\\_Title\\_SelectText\\tex_mode00.png"  ,
		L"_Images\\_Title\\_SelectText\\tex_mode01.png"  ,
		L"_Images\\_Title\\_SelectText\\tex_mode02.png"  ,
		L"_Images\\_Title\\_SelectText\\tex_mode03.png"
	},
	{
		L"_Images\\_Title\\_SelectText\\tex_operate.png" ,
		L"_Images\\_Title\\_SelectText\\tex_operate.png" ,
		L"_Images\\_Title\\_SelectText\\tex_operate.png" ,
		L"_Images\\_Title\\_SelectText\\tex_operate.png"
	}
	};

	const float				DEMO_PLAYBACK	= 10.0f;  // DEMOプレイ再生までの時間
	const float				UI_TEXT_Y[2]	= { 460.0f, 560.0f };  // 縦のUIのY座標
	const float				SPEED_ALPHA		= 127.5f;  // UIのフェード速度
	const int				MODE			= 4;  // モードの数
	const int				CHOICES			= 2;  // 縦の選択肢数

private:
	DX12::DESCRIPTORHEAP	descriptorHeap_;
	DX12::SPRITEBATCH		spriteBatch_;
	DX12::HGPUDESCRIPTOR	dx9GpuDescriptor_;

	SoundPlayer*			bgm_;
	SoundPlayer*			se_choice_;
	SoundPlayer*			se_decision_;
	MoviePlayer*			mv_bg_;
	DemoPlay*				mv_demo_;
	OriTimer*				time_start_;
	Cursor*					cursor_;
	SelectArrows*			ui_arrows_;
	Choices*				choices_;
	TextBase*				text_;
	TextUI					nowText_[2][4];
	FadeAlpha*				ui_alpha_;
	OperateUI*				operate_;
};