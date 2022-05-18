#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_UI/_Choices/Choices.h"

using namespace DirectX;

class Cursor {
public:
	Cursor();
	virtual ~Cursor();

	void Initialize();
	void LoadAsset(std::wstring file_name);
	void Update(int choices);
	void Render(float alpha) const;

	int SelectNum() const { return choices_->SelectNum(); };

private:
	const float MOVE_Y	= 102.0f;
	const float POS_X	= 435.0f - 75.0f;
	const float POS_Y	= 360.0f + 55.0f;

private:
	Choices*			choices_;
	DX9::SPRITE			sp_;
	SimpleMath::Vector3	pos_;
};