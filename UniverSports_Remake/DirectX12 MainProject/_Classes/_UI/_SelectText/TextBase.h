/**
 * @file TextBase.h
 * @brief �I�����e�L�X�g�̊��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class TextBase {
public:
	TextBase() : scale_(0.0f) {};
	virtual ~TextBase() {};

	virtual void Initialize(int modeID, DirectX::XMFLOAT3 pos) = 0;
	virtual void LoadAsset(std::wstring file_name) = 0;
	virtual void Render(float alpha) = 0;

	/**
	 * @brief �g�剉�o
	*/
	inline void GetBigger(const float deltaTime) { scale_ = std::min(scale_ + deltaTime, SCALE_MAX); };

	/**
	 * @brief �k�����o
	*/
	inline void GetSmaller(const float deltaTime) { scale_ = std::max(scale_ - deltaTime, SCALE_MIN); };

protected:
	const float SCALE_MAX = 1.35f;
	const float SCALE_MIN = 1.0f;
	const float CENTER_X = 200.0f;
	const float CENTER_Y = 50.0f;

protected:
	//! �e�L�X�g�摜
	DX9::SPRITE sprite_;

	//! �e�L�X�g���W
	DirectX::XMFLOAT3 position_;
	
	//! �e�L�X�g�T�C�Y
	float scale_;
};