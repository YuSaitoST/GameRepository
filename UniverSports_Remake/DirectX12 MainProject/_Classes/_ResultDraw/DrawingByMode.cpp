#include "DrawingByMode.h"
#include "_Classes/_ConstStrages/UIPosition.h"
#include "_Classes/_UI/_Serials/Serials.h"

DrawingByMode::DrawingByMode() : sp_playerName_(DX9::SPRITE()), sp_number_(DX9::SPRITE()), maxScore_(0), player_rect_x{0, 0}, oneDigit_x(0), twoDigit_x(0) {
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

	oneDigit_x = SERIALS::GetRectX(_oneDigit, US2D::Pos::Get().ResultParam().NUMBER_MAX, US2D::Pos::Get().ResultParam().NUMBER_RECT_X);
	twoDigit_x = SERIALS::GetRectX(_twoDigit, US2D::Pos::Get().ResultParam().NUMBER_MAX, US2D::Pos::Get().ResultParam().NUMBER_RECT_X);

	// �v���C���[���̘A�Ԃ̕\���͈͂����߂�
	player_rect_x[0] = SERIALS::GetRectX(winPlayerID[0], US2D::Pos::Get().ResultParam().PLAYER_MAX, US2D::Pos::Get().ResultParam().PLAYER_RECT_X);
	player_rect_x[1] = (DontDestroy->GameMode_.isSINGLES_GAME()) ? 0 : SERIALS::GetRectX(winPlayerID[1], US2D::Pos::Get().ResultParam().PLAYER_MAX, US2D::Pos::Get().ResultParam().PLAYER_RECT_X);
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
	DX9::SpriteBatch->DrawSimple(sp_number_.Get(), DirectX::XMFLOAT3(US2D::Pos::Get().ResultParam().NUMBER_POS_X, US2D::Pos::Get().ResultParam().NUMBER_POS_Y, (int)US2D::Layer::RESULT::UI_SCORE), RECT(twoDigit_x, 0, twoDigit_x + US2D::Pos::Get().ResultParam().NUMBER_RECT_X, US2D::Pos::Get().ResultParam().NUMBER_RECT_Y));
	DX9::SpriteBatch->DrawSimple(sp_number_.Get(), DirectX::XMFLOAT3(US2D::Pos::Get().ResultParam().NUMBER_POS_X + US2D::Pos::Get().ResultParam().NUMBER_RECT_X, US2D::Pos::Get().ResultParam().NUMBER_POS_Y, (int)US2D::Layer::RESULT::UI_SCORE), RECT(oneDigit_x, 0, oneDigit_x + US2D::Pos::Get().ResultParam().NUMBER_RECT_X, US2D::Pos::Get().ResultParam().NUMBER_RECT_Y));
}