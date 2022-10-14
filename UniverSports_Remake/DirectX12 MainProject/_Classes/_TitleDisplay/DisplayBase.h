/**
 * @file DisplayBase.h
 * @brief ��ʕ\���̐؂�ւ��̊��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "NextScene.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_InputManager/UseKeyChecker.h"

/***
 * @enum DISPLAYMODE
 * @brief �\�����
*/
enum DISPLAYMODE { 
	DISPLAY_NORMAL,		// �ʏ���
	DISPLAY_DEMO,		// �f���v���C
	DISPLAY_CONFIG,		// �ݒ���
	DISPLAY_NONE
};

class DisplayBase {
public:
	DisplayBase() {}
	virtual ~DisplayBase() {}

	DisplayBase(DisplayBase&&) = delete;
	DisplayBase& operator= (DisplayBase&&) = delete;

	DisplayBase(DisplayBase const&) = delete;
	DisplayBase& operator= (DisplayBase const&) = delete;

	virtual void Initialize() = 0;
	virtual void LoadAssets() = 0;
	virtual NextScene Update(const float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Reset() = 0;

	virtual DISPLAYMODE IsChange() = 0;
	virtual void ReDisplayInitialize() = 0;
};