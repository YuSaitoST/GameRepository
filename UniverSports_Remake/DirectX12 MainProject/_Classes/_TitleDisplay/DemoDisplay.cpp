#include "DemoDisplay.h"
#include "_Classes/_FileNames/FileNames.h"

DemoDisplay::DemoDisplay() {
	movie_ = new MoviePlayer();
}

DemoDisplay::~DemoDisplay() {
	delete movie_;
}

void DemoDisplay::Initialize() {
	//�������Ȃ�
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
 * @brief ��ʕ\����؂�ւ���ۂɕ\����Ԃ����Z�b�g����
*/
void DemoDisplay::Reset() {
	movie_->Stop();
}

/**
 * @brief ��ʕ\����؂�ւ��邩�̔���
 * @return ��������̃{�^���������ꂽ��true
*/
bool DemoDisplay::IsChange() {
	return Press.AnyKey();
}