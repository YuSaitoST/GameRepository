/**
 * @file Cursor.h
 * @brief �J�[�\���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_UI/_Choices/Choices.h"

class Cursor {
public:
	Cursor();
	virtual ~Cursor();

	Cursor(Cursor&&) = delete;
	Cursor& operator= (Cursor&&) = delete;

	Cursor(Cursor const&) = delete;
	Cursor& operator= (Cursor const&) = delete;

	void Initialize();
	void LoadAsset(std::wstring file_name);
	void Update(int choices);
	void Render(float alpha) const;

	/**
	 * @brief ���ݑI�����Ă���ԍ���Ԃ�
	 * @return �I�����Ă���ԍ�
	*/
	int SelectNum() const { return choices_->SelectNum(); };

private:
	const float MOVE_Y	= 102.0f;
	const float POS_X	= 360.0f;
	const float POS_Y	= 415.0f;

private:
	//! �I���N���X
	Choices* choices_;

	//! �J�[�\���̉摜
	DX9::SPRITE	sp_;

	//! �J�[�\���̍��W
	DirectX::SimpleMath::Vector3 pos_;
};