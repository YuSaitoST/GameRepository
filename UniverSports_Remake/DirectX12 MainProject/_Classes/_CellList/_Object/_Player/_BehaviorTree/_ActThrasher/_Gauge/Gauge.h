#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/ConstantStorages.h"
#include "_Classes/Camera/MainCamera.h"

using namespace DirectX;

class Gauge {
public:
	Gauge();
	virtual ~Gauge() = default;

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

	void IsDecrease();
	void IsRecovery();

	void SetPosition(SimpleMath::Vector3 position) { position_ = position; };

	float GetProportion() const { return proportion_; };

private:
	const int	RECT_Y		= 15;
	const float	MAX_GAUGE	= 71;
	const float GtoO		= 0.5f;
	const float OtoR		= 0.2f;

	const std::wstring FILENAME_GL[3] = {
		L"_Images\\_Main\\_Gauge\\_long\\g_green_long.png",
		L"_Images\\_Main\\_Gauge\\_long\\g_orange_long.png",
		L"_Images\\_Main\\_Gauge\\_long\\g_red_long.png"
	};

	const std::wstring FILENAME_GR[3] = {
		L"_Images\\_Main\\_Gauge\\_tip\\g_green_tip.png",
		L"_Images\\_Main\\_Gauge\\_tip\\g_orange_tip.png",
		L"_Images\\_Main\\_Gauge\\_tip\\g_red_tip.png"
	};

	enum COLOR {
		GREEN,
		ORANGE,
		RED
	} color_;

	DX9::SPRITE sp_gauge_L_[3];
	DX9::SPRITE sp_gauge_R_[3];
	DX9::SPRITE sp_flame_;

	SimpleMath::Vector3 position_;

	float movement_decrease_;
	float movement_recovery_;

	float time_delta_;
	float proportion_;
	float gauge_;
	float gauge_rect_x_;
};