/**
 * @file Finish.h
 * @brief �I�����̉��o�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class Finish {
public:
	Finish();
	virtual ~Finish() = default;

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

	/**
	* @brief �A�j���[�V�����̏I����Ԃ�Ԃ�
	* @return �A�j���[�V�����̏I�����
	*/
	bool isAnimationFine() const { return (alpha_ == 0.0f); };

private:
	const float MOVEMENT = 640.0f;

	//! �I���摜
	DX9::SPRITE sprite_;
	
	//! ���W
	DirectX::XMFLOAT3 position_;
	
	//! �A�j���[�V�����̈ړ���
	float movement_move_;
	
	//! ���l�̕ω���
	float movement_alpha_;
	
	//! �\������
	float time_display_;
	
	//! ���l
	float alpha_;
};