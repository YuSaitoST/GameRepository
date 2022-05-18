#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Base/DX12Effekseer.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

using namespace DirectX;

class EffectBase {
public:
	EffectBase() { SetMember(0.0f); }
	EffectBase(const float time) { SetMember(time); }
	virtual ~EffectBase() = default;

	virtual void SetMember(const float time) {
		effect_ = EFFECT{}; 
		timer_ = new CountTimer(time);
	}

	virtual void Initialize(std::string eff_name) { name_ = eff_name; }
	virtual void LoadAsset(std::wstring file_name) { effect_ = DX12Effect.Create(file_name.c_str(), name_); }

	virtual void ResetTime() { timer_->Reset(); }

	virtual void Set_Position(SimpleMath::Vector3 position) { DX12Effect.SetPosition(name_, position); }
	virtual void Set_Rotate(SimpleMath::Vector3 rotate) { DX12Effect.SetRotation(name_, rotate); }
	virtual void Set_Scale(SimpleMath::Vector3 scale) { DX12Effect.SetScale(name_, scale); }

	virtual void Play() { DX12Effect.Play(name_); }
	virtual void PlayOneShot() { DX12Effect.PlayOneShot(name_); }

	virtual void Pause() { DX12Effect.Pause(name_); }

	virtual void Move(SimpleMath::Vector3 movement) { DX12Effect.MoveEffect(name_, movement); }

	virtual void TimerCount(const float deltaTime) { timer_->Update(deltaTime); }

	virtual bool isOver() { return timer_->TimeOut(); }

protected:
	EFFECT		effect_;
	CountTimer*	timer_;
	std::string name_;
};