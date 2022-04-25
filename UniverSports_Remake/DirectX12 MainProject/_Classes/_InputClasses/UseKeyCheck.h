#pragma once

#include "KeyBoadChecker.h"
#include "GamePadChecker.h"

#define Press UseKeyCheck::GetInstance()

class UseKeyCheck {
public:
	static UseKeyCheck& GetInstance() { return inctance_; }

	void Accepts();

	bool AnyKey();
	bool TabKey();
	bool UpKey();
	bool DownKey();
	bool LeftKey();
	bool RightKey();
	bool DecisionKey();
	bool CancelKey();
	bool AllSelectKey();

	bool ThrasherKey(int index);
	bool ShotKey(int index);
	Vector2 MoveDirection(int index);

private:
	UseKeyCheck() {}
	virtual ~UseKeyCheck() {}

	static UseKeyCheck inctance_;
	KeyBoadChecker key_;
	GamePadChecker pad_;
};