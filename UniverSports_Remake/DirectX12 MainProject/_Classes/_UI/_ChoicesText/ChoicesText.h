/**
 * @file ChoicesText.h
 * @brief �I�����e�L�X�g�N���X
 * @author �V���D�F
 * @date 2021/09/20
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class ChoicesText {
public:
	ChoicesText() : position_(0, 0, 0), scale_(0.0f), lastID_(0) {};
	virtual ~ChoicesText() {};

	inline void Initialize(DirectX::XMFLOAT3 defaultPos) { position_ = defaultPos; }
	inline void LoadAsset(int fileCount, std::wstring file_name, ...) {
		va_list args;
		va_start(args, file_name);
		
		sprites_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, file_name.c_str()));

		std::wstring name;
		for (int i = 0; i < fileCount - 1; ++i) {
			name = va_arg(args, std::wstring);
			sprites_.push_back(DX9::Sprite::CreateFromFile(DXTK->Device9, name.c_str()));
		}

		va_end(args);
	}
	inline void Render(float alpha, int selectID) {
		DX9::SpriteBatch->Draw(
			sprites_[selectID].Get(),
			position_,
			nullptr,
			DX9::Colors::RGBA(255, 255, 255, alpha),
			DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT3(CENTER_X, CENTER_Y, 0.0f),
			DirectX::SimpleMath::Vector2::One * scale_
		);
	}

	/*
	* @brief �Ō�ɑI�����ꂽID��ێ�����
	* @param id �Ō�ɑI�����ꂽID
	*/
	inline void SetLastID(int id) { lastID_ = id; }

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
	std::vector<DX9::SPRITE> sprites_;

	//! �e�L�X�g���W
	DirectX::XMFLOAT3 position_;

	//! �e�L�X�g�T�C�Y
	float scale_;

	//! �Ō�ɑI�����ꂽ�ԍ�
	int lastID_;
};