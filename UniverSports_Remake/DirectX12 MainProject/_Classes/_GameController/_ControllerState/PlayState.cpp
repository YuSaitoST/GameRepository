#include "PlayState.h"
#include "_Classes/_GameController/GameController.h"
#include "DontDestroyOnLoad.h"

PlayState::PlayState() {
	font_ = DX9::SPRITEFONT{};
	timer_ = std::make_unique<CountTimer>(TIME_LIMIT[(int)DontDestroy->GameMode_.SelectionMode()]);
}

void PlayState::Initialize() {
	font_ = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS ゴシック", 30);
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

	DX9::SpriteBatch->DrawString(font_.Get(), DirectX::XMFLOAT2(50.0f, 100.0f), DX9::Colors::White, L"残り : %i", (int)timer_->NowTime());
}

bool PlayState::ChangeDrawing(GameController* controller) {
	controller->gamePlay_ = !controller->GameFined();
	return !controller->gamePlay_;
}