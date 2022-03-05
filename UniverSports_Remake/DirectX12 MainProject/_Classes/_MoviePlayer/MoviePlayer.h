#pragma once

#include"Base/pch.h"
#include"Base/dxtk.h"

using namespace DirectX;

class MoviePlayer {
public:
	MoviePlayer(SimpleMath::Vector3 pos, float scale);
	virtual ~MoviePlayer() {};

	void LoadAsset(std::wstring file_name);
	void Update();
	void Render() const;

	inline void Play() { media_->Play(); };
	inline void Stop() { media_->Stop(); };

	inline void SetPosition(SimpleMath::Vector3 pos) { position_ = pos; };

private:
	DX9::MEDIARENDERER media_;
	SimpleMath::Vector3 position_;
	float scale_;
};