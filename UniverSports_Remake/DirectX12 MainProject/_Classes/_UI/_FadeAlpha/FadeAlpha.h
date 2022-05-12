#pragma once

#include <algorithm>

class FadeAlpha {
public:
	FadeAlpha(float alpha, float speed);
	virtual ~FadeAlpha() {};

	void FadeIn(const float deltaTime);
	inline float Alpha() const { return ui_alpha_; };

private:
	const float MAX = 255.0f;
	float ui_alpha_;
	float speed_;
};