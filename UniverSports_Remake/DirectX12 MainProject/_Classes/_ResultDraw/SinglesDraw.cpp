#include "SinglesDraw.h"
#include "_Classes/_ConstStrages/UIPosition.h"

void SinglesDraw::Initialize() {
	int	_maxScore		= DontDestroy->Score_[0];
	int _newScore		= 0;
	int	_winnerPID[2]	= { 0, -1 };

	// シングルスのスコア計算(一番多いプレイヤーが優勝)
	for (int _i = 1; _i < 4; ++_i) {
		_newScore = DontDestroy->Score_[_i];
		if (_maxScore < _newScore) {
			_maxScore = _newScore;
			_winnerPID[0] = _i;
		}
	}

	maxScore_ = _maxScore;
	CommonCalculation(_winnerPID);
}

void SinglesDraw::LoadAssets() {
	int* _scoreList = DontDestroy->Score_;
	int _winPlayerID_0;
	for (int _i = 0; _i < 4; ++_i) {
		if (maxScore_ == _scoreList[_i]) {
			_winPlayerID_0 = DontDestroy->ChoseColor_[_i];
		}
	}
	sp_winPlayer_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::WINNERCHARA[_winPlayerID_0].c_str()));

	CommonLoadAssets();
}

void SinglesDraw::Render() {
	CommonDrawing();

	auto _pos = US2D::Pos::Get().ResultParam();
	DX9::SpriteBatch->DrawSimple(sp_playerName_.Get(), DirectX::XMFLOAT3(_pos.PLAYER_POS_X, _pos.PLAYER_POS_Y, (int)US2D::Layer::RESULT::UI_WINNERTEXT), RECT(player_rect_x[0], 0, player_rect_x[0] + _pos.PLAYER_RECT_X, _pos.PLAYER_RECT_Y));
	DX9::SpriteBatch->DrawSimple(sp_winPlayer_[0].Get(), DirectX::XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::RESULT::UI_WINNER));
}