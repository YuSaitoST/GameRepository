#include "Gauge.h"

Gauge::Gauge() {
	color_				= COLOR::GREEN;
	position_			= SimpleMath::Vector3::Zero;
	movement_decrease_	= 0.0f;
	movement_recovery_	= 0.0f;
	proportion_			= 0.0f;
	gauge_				= 0.0f;
	gauge_rect_x_		= 0.0f;
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
		sp_gauge_L_[_i] = DX9::Sprite::CreateFromFile(DXTK->Device9, FILENAME_GL[_i].c_str());
	for (int _i = 0; _i < 3; ++_i)
		sp_gauge_R_[_i] = DX9::Sprite::CreateFromFile(DXTK->Device9, FILENAME_GR[_i].c_str());

	sp_flame_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"_Images\\_Main\\_Player\\_Gauge\\flame.png");
}

void Gauge::Update(const float deltaTime, bool usedThrasher) {
	usedThrasher ? IsDecrease(deltaTime) : IsRecovery(deltaTime);

	proportion_		= std::min(std::max(0.1f, (gauge_ / MAX_GAUGE)), 1.0f);

	gauge_rect_x_	= MAX_GAUGE * proportion_;

	color_ = (GtoO <= proportion_) ? COLOR::GREEN  :
			 (OtoR <= proportion_) ? COLOR::ORANGE :
									 COLOR::RED;
}

void Gauge::Render() {
	if (proportion_ == 1.0f)
		return;

	position_ = DXTK->Direct3D9->WorldToScreenPoint(position_, Camera.GetCamera());
	position_ += SimpleMath::Vector3(-35.0f, -60.0f, 0.0f);

	DX9::SpriteBatch->DrawSimple(sp_gauge_L_[color_].Get(), SimpleMath::Vector3(position_.x, position_.y, -999.0f), RECT(0.0f, 0.0f, gauge_rect_x_, RECT_Y));
	DX9::SpriteBatch->DrawSimple(sp_gauge_R_[color_].Get(), SimpleMath::Vector3(position_.x - MAX_GAUGE + gauge_rect_x_, position_.y, -998.0f));
	DX9::SpriteBatch->DrawSimple(sp_flame_			.Get(), SimpleMath::Vector3(position_.x, position_.y, -997.0f), nullptr, DX9::Colors::RGBA(255, 255, 255, 255));  // GBÇ20Ç≠ÇÁÇ¢Ç…Ç∑ÇÈÇ∆ê‘îwåiÇ…Ç»ÇÈ
}

void Gauge::IsDecrease(const float deltaTime) {
	gauge_ = std::max(0.0f, gauge_ - movement_decrease_ * deltaTime);
}

void Gauge::IsRecovery(const float deltaTime) {
	gauge_ = std::min(gauge_ + movement_recovery_ * deltaTime, MAX_GAUGE);
}