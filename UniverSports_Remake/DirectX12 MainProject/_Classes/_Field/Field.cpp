#include "Field.h"
#include "_Classes/_StandardCalculation/StandardCalculation.h"

/**
* @brief 画面内に収める
* @param position 座標
*/
void FIELD::Clamp(DirectX::SimpleMath::Vector2& position) {
	StandardCalculation::Clamp(position.x, -HALF_X, HALF_X);
	StandardCalculation::Clamp(position.y, -HALF_Y, HALF_Y);
}

/**
* @brief 画面外に出たら、反対方向から出す
* @param position 座標
*/
void FIELD::ClampLoop(DirectX::SimpleMath::Vector2& position) {
	StandardCalculation::ValueLoop(position.x, -HALF_X, HALF_X);
	StandardCalculation::ValueLoop(position.y, -HALF_Y, HALF_Y);
}

/**
* @brief 画面外に出たかを返す
* @param position 座標
* @param radius 半径
* @return 画面外に出たらtrue  内側ならfalse
*/
bool FIELD::IsOut(DirectX::SimpleMath::Vector2 position, float raidus) {
	const bool isOutX = (position.x + raidus < -HALF_X) || (HALF_X < position.x - raidus);
	const bool isOutY = (position.y + raidus < -HALF_Y) || (HALF_Y < position.y - raidus);

	return isOutX || isOutY;
}