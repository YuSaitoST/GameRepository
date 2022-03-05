#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class TextBase {
public:
	TextBase() = default;
	virtual ~TextBase() = default;

	virtual void Initialize(int modeID, SimpleMath::Vector3 pos) = 0;
	virtual void LoadAsset(std::wstring file_name) = 0;
	virtual void Render(float alpha) = 0;

	inline void GetBigger(const float deltaTime) 
		{ scale_ = std::min(scale_ + deltaTime, SCALE_MAX); };
	inline void GetSmaller(const float deltaTime) 
		{ scale_ = std::max(scale_ - deltaTime, SCALE_MIN); };

	virtual int MyID() const { return modeID_; };

protected:
	const float SCALE_MAX = 1.35f;
	const float SCALE_MIN = 1.0f;
	const float CENTER_X = 200.0f;
	const float CENTER_Y = 50.0f;

protected:
	DX9::SPRITE sprite_;
	SimpleMath::Vector3 position_;
	float scale_;
	int modeID_;
};