#include "PlayState.h"
#include "_Classes/_GameController/GameController.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "DontDestroyOnLoad.h"

PlayState::PlayState() {
	font_	= DX9::SPRITEFONT{};
	timer_	= std::make_unique<CountTimer>(GAMES_PARAM.MN_GAMETIMER[(int)DontDestroy->GameMode_.SelectionMode()]);
}

void PlayState::Initialize() {
	font_	= DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"MS �S�V�b�N", 20);
}

void PlayState::LoadAsstes() {
	//���[�h�Ȃ�
}

void PlayState::Update(const float deltaTime) {
	timer_->Update(deltaTime);
}

void PlayState::Render() {
	if (timer_->TimeOut())
		return;

	//�e�L�X�g����ԑO�ɕ`�悷��悤�ɒ���
	DirectX::XMMATRIX _matrix = DirectX::SimpleMath::Matrix::CreateTranslation(0.0f, 0.0f, (int)US2D::Layer::MAIN::UI_COUNTDOWN);
	DXTK->Direct3D9->SetTransform(D3DTS_WORLD, *(D3DMATRIX*)&_matrix);
	DX9::SpriteBatch->SetTransform(_matrix);

	DX9::SpriteBatch->DrawString(font_.Get(), US2D::Pos::Get().MainParam().TIMER, DX9::Colors::White, L"�c�� : %i", (int)timer_->NowTime());

	_matrix = DirectX::SimpleMath::Matrix::Identity;
	DXTK->Direct3D9->SetTransform(D3DTS_WORLD, *(D3DMATRIX*)&_matrix);
	DX9::SpriteBatch->ResetTransform();

}

bool PlayState::ChangeDrawing(GameController* controller) {
	controller->gamePlay_ = !controller->GameFined();
	return !controller->gamePlay_;
}