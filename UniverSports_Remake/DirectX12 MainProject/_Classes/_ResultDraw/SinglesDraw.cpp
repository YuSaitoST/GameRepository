#include "SinglesDraw.h"
#include "_Classes/_ConstStrages/UIPosition.h"

void SinglesDraw::Initialize() {
	int _winPlayerID[2] = { -1,-1 };

	// シングルスのスコア計算(一番多いプレイヤーが優勝)
	for (int _i = 0; _i < 4; ++_i) {
		if (maxScore_ < DontDestroy->Score_[_i]) {
			maxScore_ = DontDestroy->Score_[_i];
			_winPlayerID[0] = _i;
		}
	}

	CommonCalculation(_winPlayerID);
}

void SinglesDraw::LoadAssets() {
	const int _winPlayerID_0 = player_rect_x[0] / US2D::Pos::Get().ResultParam().PLAYER_RECT_X;
	sp_winPlayer_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::WINNERCHARA[_winPlayerID_0].c_str()));

	CommonLoadAssets();
}

void SinglesDraw::Render() {
	CommonDrawing();

	DX9::SpriteBatch->DrawSimple(sp_winPlayer_[0].Get(), DirectX::XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::RESULT::UI_WINNER));
	DX9::SpriteBatch->DrawSimple(sp_playerName_.Get(), DirectX::XMFLOAT3(US2D::Pos::Get().ResultParam().PLAYER_POS_X, US2D::Pos::Get().ResultParam().PLAYER_POS_Y, (int)US2D::Layer::RESULT::UI_WINNERTEXT), RECT(player_rect_x[0], 0, player_rect_x[0] + US2D::Pos::Get().ResultParam().PLAYER_RECT_X, US2D::Pos::Get().ResultParam().PLAYER_RECT_Y));
}