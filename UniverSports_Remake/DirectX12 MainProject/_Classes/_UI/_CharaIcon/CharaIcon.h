#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class CharaIcon {
public:
	CharaIcon() {}
	virtual ~CharaIcon() {}

	void Initialize(SimpleMath::Vector3 pos);
	void LoadAssets(std::wstring file_name);
	void Render(const int life, float alpha);

private:
	SimpleMath::Vector3 pos_;
	DX9::SPRITE sprite_;

	const int SIZE = 40;
};