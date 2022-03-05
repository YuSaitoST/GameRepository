#pragma once

#include <algorithm>

class FadeAlpha {
public:
	FadeAlpha(float alpha, float speed);
	virtual ~FadeAlpha() {};

	void Update(const float deltaTime);

	void FadeIn();
	void FadeOut();

	inline float Alpha() const { return ui_alpha_; };

private:
	const float MAX = 255.0f;
	float ui_alpha_;
	float speed_;
};