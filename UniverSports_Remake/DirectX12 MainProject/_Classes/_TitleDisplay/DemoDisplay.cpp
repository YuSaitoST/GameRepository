#include "DemoDisplay.h"
#include "_Classes/_FileNames/FileNames.h"

DemoDisplay::DemoDisplay() {
	movie_ = new MoviePlayer();
}

DemoDisplay::~DemoDisplay() {
	delete movie_;
}

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
	movie_->Render();
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
bool DemoDisplay::IsChange() {
	return Press.AnyKey();
}