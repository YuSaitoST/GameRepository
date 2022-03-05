#pragma once

#include "InputBase.h"

class InputBaseKey : public InputBase {
public:
	inline void ResetMember() {
		flag_	= 0;
		direct_ = Vector2::Zero;
	}

	inline bool CharaKey(char inputKey) {
		const int _index = (int)inputKey - (int)'A';
		return (flag_ & (1 << _index));
	}

	inline bool ArrowKey(int inputKey) {
		const int _index = inputKey + CHARA;
		return (flag_ & (1 << _index));
	}

	inline bool AnyKey() {
		return (flag_ & 0xffffffff);
	}

	inline Vector2 Direction() {
		if (flag_ & (1 << UP))    direct_.y = 1;
		if (flag_ & (1 << DOWN))  direct_.y = -1;
		if (flag_ & (1 << LEFT))  direct_.x = -1;
		if (flag_ & (1 << RIGHT)) direct_.x = 1;
		direct_.Normalize();
		return direct_;
	}

protected:
	// ”h¶ƒNƒ‰ƒX“à‚Å‚µ‚©Žg‚í‚È‚¢‚Ì‚Åprotected
	enum KEY {
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	unsigned int flag_;
	Vector2 direct_;

private:
	const int CHARA = 26;
};