/**
 * @file UseTeamColor.h
 * @brief �L�����N�^�[���I����Ԃ̕`��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "UserInputRender.h"

class UnSelectedRender : public UserInputRender {
public:
	UnSelectedRender() : sp_decision_(DX9::SPRITE{}) {}
	virtual ~UnSelectedRender() {}

	virtual void LoadAssets() override;
	virtual void Render(int playerID) override;

private:
	DX9::SPRITE sp_decision_;	//! ����
};