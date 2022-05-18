#include "Barrier.h"

Barrier::Barrier() : mod_(nullptr), isInvincible_(false) {
	timer_ = new CountTimer(GAME_CONST.PL_InvincibleTime);
}

Barrier::~Barrier() {
	delete timer_;
}

void Barrier::LoadAsset(float radius) {
	mod_ = DX9::Model::CreateSphere(DXTK->Device9, radius * 1.25f, 10, 10);
	SetMaterial();
}

void Barrier::Update(const float deltaTime) {
	if (isInvincible_) {
		timer_->Update(deltaTime);
		isInvincible_ = !timer_->TimeOut();

		// タイマーリセット
		if (!isInvincible_) {
			timer_->Reset();
		}
	}
}

void Barrier::Render() {
	if (isInvincible_) {
		DXTK->Direct3D9->AlphaBendEnable(true);
		mod_->Draw();
		DXTK->Direct3D9->AlphaBendEnable(false);
	}
}

void Barrier::SetMaterial() {
	D3DMATERIAL9 _mate{};
	_mate.Diffuse	= DX9::Colors::Value(1.0f, 1.0f, 1.0f, 0.25f);
	_mate.Ambient	= DX9::Colors::Value(1.0f, 1.0f, 1.0f, 0.25f);
	mod_->SetMaterial(_mate);
}