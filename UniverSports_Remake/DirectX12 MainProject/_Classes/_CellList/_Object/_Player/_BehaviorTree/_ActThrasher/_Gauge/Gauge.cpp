#include "Gauge.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/US2DLayer.h"

Gauge::Gauge() :	position_(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)),
					movement_decrease_(0.0f),
					movement_recovery_(0.0f),
					proportion_(0.0f),
					gauge_(0.0f),
					gauge_rect_x_(0.0f)
{
	color_				= GAUGECOLOR::GREEN;
}

void Gauge::Initialize() {
	movement_decrease_	= MAX_GAUGE / GAME_CONST.AMOUNT_OF_DECREASE;
	movement_recovery_	= MAX_GAUGE / GAME_CONST.AMOUNT_OF_RECOVERY;
	proportion_			= 1.0f;
	gauge_				= MAX_GAUGE;
	gauge_rect_x_		= MAX_GAUGE;
}

void Gauge::LoadAssets() {
	for (int _i = 0; _i < 3; ++_i)
		sp_gauge_L_[_i] = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::GAUGE_LEFT[_i].c_str());
	for (int _i = 0; _i < 3; ++_i)
		sp_gauge_R_[_i] = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::GAUGE_RIGHT[_i].c_str());

	sp_flame_ = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::GAUGE_FLAME.c_str());
}

void Gauge::Update(const float deltaTime, bool usedThrasher) {
	usedThrasher ? 
		IsDecrease(gauge_, movement_decrease_ * deltaTime, 0.0f) : 
		IsRecovery(gauge_, movement_recovery_ * deltaTime, MAX_GAUGE);

	proportion_		= std::min(std::max(0.1f, (gauge_ / MAX_GAUGE)), 1.0f);

	gauge_rect_x_	= MAX_GAUGE * proportion_;

	color_ = (GtoO <= proportion_) ? GAUGECOLOR::GREEN  :
			 (OtoR <= proportion_) ? GAUGECOLOR::ORANGE :
									 GAUGECOLOR::RED;
}

void Gauge::Render() {
	if (proportion_ == 1.0f)
		return;

	position_ = DXTK->Direct3D9->WorldToScreenPoint(position_, Camera.GetCamera());
	position_ += DISPLAY_POSITION;

	DX9::SpriteBatch->DrawSimple(sp_gauge_L_[color_].Get(), DirectX::XMFLOAT3(position_.x, position_.y, (int)US2D::Layer::MAIN::UI_GAUGE), RECT(0.0f, 0.0f, gauge_rect_x_, RECT_Y));
	DX9::SpriteBatch->DrawSimple(sp_gauge_R_[color_].Get(), DirectX::XMFLOAT3(position_.x - MAX_GAUGE + gauge_rect_x_, position_.y, (int)US2D::Layer::MAIN::UI_GAUGE));
	DX9::SpriteBatch->DrawSimple(sp_flame_.Get(), DirectX::XMFLOAT3(position_.x, position_.y, (int)US2D::Layer::MAIN::UI_GAUGE_FRAME), nullptr, DX9::Colors::RGBA(255, 255, 255, 255));  // GBÇ20Ç≠ÇÁÇ¢Ç…Ç∑ÇÈÇ∆ê‘îwåiÇ…Ç»ÇÈ
}