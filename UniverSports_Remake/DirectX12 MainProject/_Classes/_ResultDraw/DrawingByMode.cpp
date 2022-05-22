#include "DrawingByMode.h"

DrawingByMode::DrawingByMode() : sp_playerName_(DX9::SPRITE()), sp_number_(DX9::SPRITE()) {
	//�������m��
	const int _numberOfWinner = DontDestroy->GameMode_.isSINGLES_GAME() ? 1 : 2;
	sp_winPlayer_.reserve(_numberOfWinner);
}

/**
 * @brief ���ʂ���A�Ԍv�Z
 * @param winPlayerID ���������v���C���[��ID
*/
void DrawingByMode::CommonCalculation(int* winPlayerID) {
	// �����A�Ԃ̕\���͈͂����߂�
	const int _oneDigit = maxScore_ % 10;
	const int _twoDigit = (maxScore_ - _oneDigit) * 0.5f;

	oneDigit_x = SERIALS::GetRectX(_oneDigit, SERIALS::NUMBER::MAX, SERIALS::NUMBER::RECT_X);
	twoDigit_x = SERIALS::GetRectX(_twoDigit, SERIALS::NUMBER::MAX, SERIALS::NUMBER::RECT_X);

	// �v���C���[���̘A�Ԃ̕\���͈͂����߂�
	player_rect_x[0] = SERIALS::GetRectX(winPlayerID[0], SERIALS::PLAYER::MAX, SERIALS::PLAYER::RECT_X);
	player_rect_x[1] = (DontDestroy->GameMode_.isSINGLES_GAME()) ? 0 : SERIALS::GetRectX(winPlayerID[1], SERIALS::PLAYER::MAX, SERIALS::PLAYER::RECT_X);
}

/**
 * @brief ���ʂ���摜�̓ǂݍ���
*/
void DrawingByMode::CommonLoadAssets() {
	sp_playerName_	= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::TEX_PLAYER.c_str());
	sp_number_		= DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::NUMBER.c_str());
}

/**
 * @brief ���ʂ���`��
*/
void DrawingByMode::CommonDrawing() {
	DX9::SpriteBatch->DrawSimple(sp_number_.Get(), Vector3(SERIALS::NUMBER::POS_X, SERIALS::NUMBER::POS_Y, -3.0f), RECT(twoDigit_x, 0, twoDigit_x + SERIALS::NUMBER::RECT_X, SERIALS::NUMBER::RECT_Y));
	DX9::SpriteBatch->DrawSimple(sp_number_.Get(), Vector3(SERIALS::NUMBER::POS_X + SERIALS::NUMBER::RECT_X, SERIALS::NUMBER::POS_Y, -3.0f), RECT(oneDigit_x, 0, oneDigit_x + SERIALS::NUMBER::RECT_X, SERIALS::NUMBER::RECT_Y));
}