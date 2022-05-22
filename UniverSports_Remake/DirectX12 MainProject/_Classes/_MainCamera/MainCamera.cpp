#include"MainCamera.h"
#include "_Classes/_Field/Field.h"

using namespace DirectX;

/**
* @brief カメラの設定
*/
void MainCamera::Register()
{
	//平行投射にする
	camera_->SetOrthographic(128.0f * 0.48f, 72.0f * 0.48f, 1.0f, 10000.0f);

	//位置・視点を設定
	camera_->SetViewLookAt(
		SimpleMath::Vector3(0.0f, 0.0f, -10.0f),
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		SimpleMath::Vector3::Up
	);

	//カメラを登録
	DXTK->Direct3D9->SetCamera(camera_);
}