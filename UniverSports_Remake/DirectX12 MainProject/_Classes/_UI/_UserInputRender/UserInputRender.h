/**
 * @file UserInputRender.h
 * @brief �L�����N�^�[�I���̓��͏�Ԋ��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class UserInputRender {
public:
	UserInputRender() {}
	virtual ~UserInputRender() {}

	virtual void LoadAssets() = 0;
	virtual void Render(int playerID) = 0;
};