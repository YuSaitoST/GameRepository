#pragma once

#include "TextBase.h"

class TextUI : public TextBase {
public:
	TextUI() = default;
	virtual ~TextUI() = default;

	virtual void Initialize(int modeID, SimpleMath::Vector3 pos);
	virtual void LoadAsset(std::wstring file_name);
	virtual void Render(float alpha);
};