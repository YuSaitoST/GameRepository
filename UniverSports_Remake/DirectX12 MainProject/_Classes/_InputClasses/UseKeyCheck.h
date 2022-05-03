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
	bool UpKey(const int index);
	bool DownKey(const int index);
	bool LeftKey(const int index);
	bool RightKey(const int index);
	bool KDecisionKey();
	bool PDecisionKey(const int index);
	bool KCancelKey();
	bool PCancelKey(const int index);

	bool ThrasherKey(const int index);
	bool ShotKey(const int index);
	Vector2 MoveDirection(const int index);

private:
	UseKeyCheck() {}
	virtual ~UseKeyCheck() {}

	static UseKeyCheck inctance_;
	KeyBoadChecker key_;
	GamePadChecker pad_;
};