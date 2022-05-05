#pragma once

#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_UI/_Choices/Choices.h"
#include "_Classes/_UI/_SelectArrows/SelectArrows.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"

class CharaSelect {
public:
	CharaSelect();
	virtual ~CharaSelect();

	void Initialize(int index);
	void LoadAssets(DX9::SPRITE right, DX9::SPRITE left);
	void Update(const float deltaTime, const int index);
	void Render(DX9::SPRITE& icon, DX9::SPRITE& decisions, DX9::SPRITE entry, int index);

	bool IsDecision() const { return isDecision_; }

private:
	void SelectToAvoidDupLicates(int index);
	bool haveSameValue(int index);
	static void ValueLoop(int& num, int min, int max);

	const float INPUT_Y = 686.0f;
	const float ENTRY_Y = 585.0f;
	const float ARROW_Y = 600.0f;
	const float PICON_Y = 510.0f;

	const float TEAM_COL_X[4] = { 84.0f, 375.0f, 676.0f, 969.0f };
	const float TEAM_COL_Y = 493.5f;

	const float INPUT_X[4] = { 140.0f, 432.0f, 735.0f, 10295.0f };

	const float ENTRY_X[4] = { 108.0f, 400.0f, 702.0f, 991.0f };
	const float ARROW_L_X[4] = { 100.0f, 389.0f, 691.0f, 981.0f };
	const float ARROW_R_X[4] = { 283.0f, 572.0f, 874.0f, 1164.0f };
	const float PICON_X[4] = { ENTRY_X[0] - 5.0f, ENTRY_X[1] - 5.0f, ENTRY_X[2] - 5.0f, ENTRY_X[3] - 5.0f };

	Choices* choices_;
	SelectArrows* ui_arrows_;
	SoundPlayer* se_decision_;
	SoundPlayer* se_cancel_;
	bool isDecision_;
	bool isCansel_;
};