#pragma once

#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_UI/_Choices/Choices.h"
#include "_Classes/_UI/_SelectArrows/SelectArrows.h"

class CharaSelect {
public:
	CharaSelect();
	virtual ~CharaSelect();

	void Initialize();
	void LoadAssets(DX9::SPRITE right, DX9::SPRITE left);
	void Update(const float deltaTime, const int index);
	void Render();

private:
	void Choose();

	Choices* choices_;
	SelectArrows* ui_arrows_;
};