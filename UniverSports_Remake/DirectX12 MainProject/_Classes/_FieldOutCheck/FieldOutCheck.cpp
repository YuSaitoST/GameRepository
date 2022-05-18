#include "FieldOutCheck.h"
#include "_Classes/_StandardCalculation/StandardCalculation.h"

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
	const bool isOutX = (position.x + raidus < -SIDE_X) || (SIDE_X < position.x - raidus);
	const bool isOutY = (position.y + raidus < -SIDE_Y) || (SIDE_Y < position.y - raidus);

	return isOutX || isOutY;
}