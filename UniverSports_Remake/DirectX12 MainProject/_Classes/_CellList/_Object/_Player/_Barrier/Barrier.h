#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

using namespace DirectX;

class Barrier {
public:
	Barrier();
	virtual ~Barrier();

	void LoadAsset(float radius);
	void Update(const float deltaTime);
	void Render();

	void SetPosition(SimpleMath::Vector3 position) { mod_->SetPosition(position); };
	void DisprayOn() { isInvincible_ = true; }

	inline bool IsDisplayed() const { return isInvincible_; }

private:
	void SetMaterial();

	CountTimer* timer_;
	DX9::MODEL mod_;
	bool isInvincible_;
};