#include "DoublesDraw.h"
#include "_Classes/_ConstStrages/US2DLayer.h"

void DoublesDraw::Initialize() {
	int _winPlayerID[2] = { -1,-1 };

	// チームごとにPlayerIDをまとめる
	int _indexOfTeam0 = 0;
	int _indexOfTeam1 = 0;
	int _IDofTeam0[2] = { 0, 0 };
	int _IDofTeam1[2] = { 0, 0 };
	for (int _i = 0; _i < 4; ++_i) {
		if (DontDestroy->TeamID[_i] == 0) {
			_IDofTeam0[_indexOfTeam0] = _i;
			_indexOfTeam0 += 1;
		}
		else {
			_IDofTeam1[_indexOfTeam1] = _i;
			_indexOfTeam1 += 1;
		}
	}

	// チームごとのスコアを算出
	const int _scoreOfTeam0 = DontDestroy->Score_[_IDofTeam0[0]] + DontDestroy->Score_[_IDofTeam0[1]];
	const int _scoreOfTeam1 = DontDestroy->Score_[_IDofTeam1[0]] + DontDestroy->Score_[_IDofTeam1[1]];
	if (_scoreOfTeam0 < _scoreOfTeam1) {
		// チーム1勝利
		maxScore_ = _scoreOfTeam1;
		_winPlayerID[0] = _IDofTeam1[0];
		_winPlayerID[1] = _IDofTeam1[1];
	}
	else if (_scoreOfTeam1 < _scoreOfTeam0) {
		// チーム0勝利
		maxScore_ = _scoreOfTeam0;
		_winPlayerID[0] = _IDofTeam0[0];
		_winPlayerID[1] = _IDofTeam0[1];
	}
	else {
		// 同点
		maxScore_ = _scoreOfTeam0;
		_winPlayerID[0] = 99;
		_winPlayerID[1] = 99;
	}

	CommonCalculation(_winPlayerID);
}

void DoublesDraw::LoadAssets() {
	const int _winPlayerID_0 = player_rect_x[0] / SERIALS::PLAYER::RECT_X;
	const int _winPlayerID_1 = player_rect_x[1] / SERIALS::PLAYER::RECT_X;

	sp_winPlayer_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::WINNERCHARA[_winPlayerID_0].c_str()));
	sp_winPlayer_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::WINNERCHARA[_winPlayerID_1].c_str()));

	CommonLoadAssets();
}

void DoublesDraw::Render() {
	CommonDrawing();

	DX9::SpriteBatch->DrawSimple(sp_winPlayer_[0].Get(), DirectX::XMFLOAT3(100.0f, 0.0f, (int)US2D::Layer::RESULT::UI_WINNER));
	DX9::SpriteBatch->DrawSimple(sp_winPlayer_[1].Get(), DirectX::XMFLOAT3(-226.0f, 0.0f, (int)US2D::Layer::RESULT::UI_WINNER));
	DX9::SpriteBatch->DrawSimple(sp_playerName_.Get(), DirectX::XMFLOAT3(SERIALS::PLAYER::POS_X - 50.0f, SERIALS::PLAYER::POS_Y, (int)US2D::Layer::RESULT::UI_WINNERTEXT), RECT(player_rect_x[0], 0, player_rect_x[0] + SERIALS::PLAYER::RECT_X, SERIALS::PLAYER::RECT_Y));
	DX9::SpriteBatch->DrawSimple(sp_playerName_.Get(), DirectX::XMFLOAT3(SERIALS::PLAYER::POS_X + SERIALS::PLAYER::RECT_X - 50.0f, SERIALS::PLAYER::POS_Y, (int)US2D::Layer::RESULT::UI_WINNERTEXT), RECT(player_rect_x[1], 0, player_rect_x[1] + SERIALS::PLAYER::RECT_X, SERIALS::PLAYER::RECT_Y));
}