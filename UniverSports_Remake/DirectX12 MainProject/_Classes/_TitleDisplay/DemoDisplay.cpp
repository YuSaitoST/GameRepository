#include "DemoDisplay.h"
#include "_Classes/_ConstStrages/US2DLayer.h"

void DemoDisplay::Initialize() {
	//初期化なし
}

void DemoDisplay::LoadAssets() {
	movie_->LoadAsset(USFN_MV::TITLE_DEMO);
}

NextScene DemoDisplay::Update(const float deltaTime) {
	movie_->Update();

	return NextScene::Continue;
}

void DemoDisplay::Render() {
	movie_->Render(DirectX::XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::TITLE::BG_DEMO));
}

/**
 * @brief 画面表示を切り替える際に表示状態をリセットする
*/
void DemoDisplay::Reset() {
	movie_->Stop();
}

/**
 * @brief 画面表示を切り替えるかの判定
 * @return 何かしらのボタンが押されたらtrue
*/
DISPLAYMODE DemoDisplay::IsChange() {
	return INPSystem.AnyKey() ?
		DISPLAYMODE::DISPLAY_NORMAL :
		DISPLAYMODE::DISPLAY_NONE;
}

void DemoDisplay::ReDisplayInitialize() {
	movie_->Play();
}