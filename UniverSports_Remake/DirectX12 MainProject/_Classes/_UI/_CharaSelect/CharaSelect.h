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
	void Render(DX9::SPRITE& icon, DX9::SPRITE& decisions, DX9::SPRITE entry, SimpleMath::Vector3 adjustment);

	bool IsDecision() const { return isDecision_; }

private:
	const float INPUT_Y = 686.0f;
	const float ENTRY_Y = 585.0f;
	const float ARROW_Y = 600.0f;
	const float PICON_Y = 510.0f;

	Choices* choices_;
	SelectArrows* ui_arrows_;
	bool isDecision_;
};