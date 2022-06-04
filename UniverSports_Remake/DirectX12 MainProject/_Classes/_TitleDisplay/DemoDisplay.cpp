#include "DemoDisplay.h"
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_ConstStrages/US2DLayer.h"
#include "_Classes/_FileNames/FileNames.h"

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
	movie_->Render(DirectX::XMFLOAT3(0.0f, 0.0f, (int)US2D::Layer::TITLE::BG_DEMO));
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