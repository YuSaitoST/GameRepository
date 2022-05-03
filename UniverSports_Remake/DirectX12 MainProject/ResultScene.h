//
// TemplateScene.h
//

#pragma once

#include "Scene.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"
#include "_Classes/_MoviePlayer/MoviePlayer.h"
#include "_Classes/_UI/_BlackOut/BlackOut.h"

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

	void Render_WinChara();
	void Render_WinCName();

	void Mode_0();
	void Mode_1();
	void Mode_2();

private:
	struct PLAYER {
		static const int	POS_X	= 115;
		static const int	POS_Y	= 250;
		static const int	RECT_X	= 270;
		static const int	RECT_Y	= 135;
	};
	struct NUMBER {
		static const int	POS_X	= 360;
		static const int	POS_Y	= 462;
		static const int	RECT_X	= 50;  // 210;
		static const int	RECT_Y	= 75;  // 150;
	};

	DX12::DESCRIPTORHEAP	descriptorHeap_;
	DX12::SPRITEBATCH		spriteBatch_;
	DX12::HGPUDESCRIPTOR	dx9GpuDescriptor_;

	DX9::SPRITE				sp_winPlayer_[2];

	DX9::SPRITE				sp_bg_tile_;
	DX9::SPRITE				sp_texWin_;
	DX9::SPRITE				sp_texPressB_;
	DX9::SPRITE				sp_texCrushing_;
	DX9::SPRITE				sp_playerName_;
	DX9::SPRITE				sp_number_;

	SoundPlayer*			bgm_;
	SoundPlayer*			se_decision_;
	MoviePlayer*			bg_movie_;
	BlackOut*				blackOut_;

	int						maxScore_;
	int						winPlayerID_[2];

	int						player_x[2];
	int						oneDigit_x;
	int						twoDigit_x;

	bool					goNext_;
};