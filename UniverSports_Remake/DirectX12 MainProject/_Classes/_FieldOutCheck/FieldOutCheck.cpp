#include "FieldOutCheck.h"
#include "_Classes/_StandardCalculation/StandardCalculation.h"
#include "_Classes/_ConstStrages/ConstStorages.h"

/**
* @brief ��ʊO�ɏo����A���Ε�������o��
* @param position �`�F�b�N������W
*/
void FIELD::ClampLoop(DirectX::SimpleMath::Vector2& position) {
	StandardCalculation::ValueLoop(position.x, -GAME_CONST.FieldSide_X, GAME_CONST.FieldSide_X);
	StandardCalculation::ValueLoop(position.y, -GAME_CONST.FieldSide_Y, GAME_CONST.FieldSide_Y);
}

/**
* @brief ��ʊO�ɏo������Ԃ�
* @param position ���̂̍��W
* @param radius ���̂̔��a
* @return ��ʊO�ɏo����true  �����Ȃ�false
*/
bool FIELD::IsOut(DirectX::SimpleMath::Vector2 position, float raidus) {
	const bool isOutX = (position.x + raidus < -GAME_CONST.FieldSide_X) || (GAME_CONST.FieldSide_X < position.x - raidus);
	const bool isOutY = (position.y + raidus < -GAME_CONST.FieldSide_Y) || (GAME_CONST.FieldSide_Y < position.y - raidus);

	return isOutX || isOutY;
}