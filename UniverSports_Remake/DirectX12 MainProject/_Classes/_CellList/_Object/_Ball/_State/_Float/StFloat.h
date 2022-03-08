#pragma once

#include <random>
#include "Base/pch.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/_CellList/_Object/_Ball/_State/BallState.h"

using namespace DirectX;

class StFloat final : public BallState {
public:
	StFloat();
	virtual ~StFloat();

	virtual void Initialize() override;
	virtual void Update(const float deltaTime, ObjBall* ball) override;

private:
	SimpleMath::Vector2 RandomPosition();
	SimpleMath::Vector2 RandomDirection(SimpleMath::Vector2 pos);
	void ReSpone(SimpleMath::Vector2& position, SimpleMath::Vector2& forward);

	std::mt19937							randomEngine;
	std::uniform_int_distribution<>			pos_start_x;
	std::uniform_int_distribution<>			pos_start_y;
	std::uniform_real_distribution<float>	direct_x;
	std::uniform_real_distribution<float>	direct_y;

	float limit_pos_x;
	float limit_pos_y;
};