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
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_MoviePlayer/MoviePlayer.h"

/***
 * @enum DISPLAYMODE
 * @brief �\�����
*/
enum DISPLAYMODE { DISPLAY_NORMAL, DISPLAY_DEMO };

class DisplayBase {
public:
	DisplayBase() {}
	virtual ~DisplayBase() {}

	virtual void Initialize() = 0;
	virtual void LoadAssets() = 0;
	virtual NextScene Update(const float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Reset() = 0;

	virtual bool IsChange() = 0;

	/**
	 * @brief ������Đ�������
	*/
	virtual void MVPlay() { movie_->Play(); }

protected:
	//!�w�i����
	MoviePlayer* movie_;
};