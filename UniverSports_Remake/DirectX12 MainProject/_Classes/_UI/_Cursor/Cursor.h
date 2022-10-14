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
	virtual ~Cursor() {}

	Cursor(Cursor&&) = delete;
	Cursor& operator= (Cursor&&) = delete;

	Cursor(Cursor const&) = delete;
	Cursor& operator= (Cursor const&) = delete;

	void Initialize(float posx, float posy, float moved);
	void LoadAsset(std::wstring file_name);
	bool Update(int choices, bool up, bool down);
	void Render(float alpha) const;

	/**
	 * @brief ���ݑI�����Ă���ԍ���Ԃ�
	 * @return �I�����Ă���ԍ�
	*/
	inline int SelectNum() const { return choices_->SelectNum(); };

	/*
	* @brief �I�������w�肷��
	* @param �I���������ԍ�
	*/
	inline void SetSelectNum(int number) { choices_->SetSelectNum(number); }

private:
	//! �I���N���X
	std::unique_ptr<Choices> choices_;

	//! �J�[�\���̉摜
	DX9::SPRITE	sp_;

	//! �J�[�\���̍��W
	DirectX::SimpleMath::Vector3 pos_;

	//! �ړ���
	float moved_;

	//! �J�nY���W
	float startPos_Y_;
};