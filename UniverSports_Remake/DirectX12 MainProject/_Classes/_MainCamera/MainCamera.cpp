#include"MainCamera.h"
#include "_Classes/_Field/Field.h"

using namespace DirectX;

/**
* @brief �J�����̐ݒ�
*/
void MainCamera::Register()
{
	//���s���˂ɂ���
	camera_->SetOrthographic(128.0f * 0.48f, 72.0f * 0.48f, 1.0f, 10000.0f);

	//�ʒu�E���_��ݒ�
	camera_->SetViewLookAt(
		SimpleMath::Vector3(0.0f, 0.0f, -10.0f),
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		SimpleMath::Vector3::Up
	);

	//�J������o�^
	DXTK->Direct3D9->SetCamera(camera_);
}