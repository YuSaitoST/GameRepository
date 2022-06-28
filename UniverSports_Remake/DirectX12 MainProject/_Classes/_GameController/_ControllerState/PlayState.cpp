#include "PlayState.h"
#include "_Classes/_GameController/GameController.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "DontDestroyOnLoad.h"

PlayState::PlayState() {
	font_	= DX9::SPRITEFONT{};
	timer_	= std::make_unique<CountTimer>(GAMES_PARAM.MN_GAMETIMER[(int)DontDestroy->GameMode_.SelectionMode()]);
}

void PlayState::Initialize() {
	font_	= DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 20);
}

void PlayState::LoadAsstes() {
	//ロードなし
}

void PlayState::Update(const float deltaTime) {
	timer_->Update(deltaTime);
}

void PlayState::Render() {
	if (timer_->TimeOut())
		return;

	//テキストが一番前に描画されるように調整
	DirectX::XMFLOAT2 _pos		= US2D::Pos::Get().MainParam().TIMER;
	DirectX::XMMATRIX _matrix	= DirectX::SimpleMath::Matrix::CreateTranslation(_pos.x, _pos.y, (int)US2D::Layer::MAIN::UI_COUNTDOWN);
	DX9::SpriteBatch->DrawString(font_.Get(), _pos, DX9::Colors::White, _matrix, L"残り : %i", (int)timer_->NowTime());

	DX9::SpriteBatch->ResetTransform();
}

bool PlayState::ChangeDrawing(GameController* controller) {
	controller->gamePlay_ = !controller->GameFined();
	return !controller->gamePlay_;
}