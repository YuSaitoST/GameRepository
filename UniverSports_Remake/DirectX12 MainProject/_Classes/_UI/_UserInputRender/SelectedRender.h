/**
 * @file SelectedRender.h
 * @brief �L�����N�^�[�I����Ԃ̕`��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "UserInputRender.h"

class SelectedRender : public UserInputRender {
public:
	SelectedRender() : sp_cancel_(DX9::SPRITE{}), sp_entry_(DX9::SPRITE{}) {}
	virtual ~SelectedRender() {}

	virtual void LoadAssets() override;
	virtual void Render(int playerID) override;

private:
	DX9::SPRITE sp_cancel_;	//! �L�����Z��
	DX9::SPRITE sp_entry_;	//! �G���g���[
};