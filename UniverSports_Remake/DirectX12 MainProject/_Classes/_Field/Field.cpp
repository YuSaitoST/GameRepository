#include "Field.h"
#include "_Classes/_StandardCalculation/StandardCalculation.h"

//void FIELD::Clamp(DirectX::SimpleMath::Vector2& position) {
//	position.x = std::max(0.0f + 1.0f, std::min(position.x, SIDE_X - 1.0f));
//	position.y = std::max(0.0f + 1.0f, std::min(position.y, SIDE_Y - 1.0f));
//}

/**
* @brief ��ʊO�ɏo����A���Ε�������o��
* @param position �`�F�b�N������W
*/
void FIELD::ClampLoop(DirectX::SimpleMath::Vector2& position) {
	StandardCalculation::ValueLoop(position.x, -SIDE_X, SIDE_X);
	StandardCalculation::ValueLoop(position.y, -SIDE_Y, SIDE_Y);
}

/**
* @brief ��ʊO�ɏo������Ԃ�
* @param position ���̂̍��W
* @param radius ���̂̔��a
* @return ��ʊO�ɏo����true  �����Ȃ�false
*/
bool FIELD::IsOut(DirectX::SimpleMath::Vector2 position, float raidus) {
	const bool isOutX = (position.x < -SIDE_X) || (SIDE_X < position.x);
	const bool isOutY = (position.y < -SIDE_Y) || (SIDE_Y < position.y);

	return isOutX || isOutY;
}