#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX::SimpleMath;

enum KEY {
	A, B, C, D, E,
	F, G, H, I, J,
	K, L, M, N, O,
	P, Q, R, S, T,
	U, V, W, X, Y, Z,
	UP, DOWN, LEFT, RIGHT,TAB
};

class KeyBoadBase {
public:
	KeyBoadBase() : flag_(0) {}
	virtual ~KeyBoadBase() {}

	virtual void Accepts() = 0;

	inline bool OnOffKey(KEY inputKey) {
		return (flag_ & (1 << (int)inputKey));
	}

	inline bool AnyKey() {
		return (flag_ & 0xffffffff);
	}

	inline Vector2 Direction() {
		if (flag_ & (1 << UP   )) direct_.y = 1;
		if (flag_ & (1 << DOWN )) direct_.y = -1;
		if (flag_ & (1 << LEFT )) direct_.x = -1;
		if (flag_ & (1 << RIGHT)) direct_.x = 1;
		direct_.Normalize();
		return direct_;
	}

protected:
	unsigned int flag_;
	Vector2 direct_;

private:
	const int CHARA = 26;
};