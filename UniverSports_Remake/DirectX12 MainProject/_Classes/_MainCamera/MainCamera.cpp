#include"MainCamera.h"

MainCamera::MainCamera() {
	camera_ = DX9::CAMERA{};
	pos_ = SimpleMath::Vector3::Zero;
}

void MainCamera::Initialize()
{
	pos_ = SimpleMath::Vector3(0.0f, 0.0f, -10.0f);

	camera_->SetPerspectiveFieldOfView(
		XMConvertToRadians(45.0f), 16.0f / 9.0f, 1.0f, 10000.0f);

	camera_->SetOrthographic(128.0f * 0.48f, 72.0f * 0.48f, 1.0f, 10000.0f);

	DXTK->Direct3D9->SetCamera(camera_);
}

void MainCamera::Render()
{
	camera_->SetViewLookAt(
		pos_,
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		SimpleMath::Vector3::Up);

	DXTK->Direct3D9->SetCamera(camera_);
}