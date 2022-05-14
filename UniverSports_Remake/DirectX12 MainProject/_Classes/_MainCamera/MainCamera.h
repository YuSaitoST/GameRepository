/**
 * @file MainCamera.h
 * @brief �J�����N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include"Base/pch.h"
#include"Base/dxtk.h"

//�}�N��
#define Camera MainCamera::GetInstance()

class MainCamera {
public:
	MainCamera();
	virtual ~MainCamera() {};

	static MainCamera& GetInstance() {
		static MainCamera _inctance;
		return _inctance;
	}

	void Register();

	/**
	* @brief �J������Ԃ�
	* @return �J����
	*/
	DX9::CAMERA GetCamera() const { return camera_; };

private:
	DX9::CAMERA camera_;
};