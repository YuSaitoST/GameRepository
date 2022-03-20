#pragma once

#include <random>
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

class StFloat : public BallState {
public:
	StFloat() = default;
	virtual ~StFloat() = default;

	virtual void Initialize();
	virtual void Update(ObjBall* ball);

private:
	SimpleMath::Vector2 RandomPosition();
	SimpleMath::Vector2 RandomForward(const SimpleMath::Vector2 position);
	void SetTransform();
	void ReSpone(ObjBall* ball);

	void CheckFieldOut(ObjBall* ball);
	void LoopPos(ObjBall* ball);

private:
	std::mt19937							randomEngine;
	std::uniform_int_distribution<>			pos_start_x;
	std::uniform_int_distribution<>			pos_start_y;
	std::uniform_real_distribution<float>	direct_x;
	std::uniform_real_distribution<float>	direct_y;

	float limit_pos_x;
	float limit_pos_y;
	float limit_direct_x;
	float limit_direct_y;

private:
	// MODE { 0 Å` 3 }
	// MODE / 3 { 0 , 0 , 0 , 1 }
	const float DIRECT_X[2] = { 5.5f,5.5f };
	const float DIRECT_Y[2] = { 5.5f,5.5f };
};