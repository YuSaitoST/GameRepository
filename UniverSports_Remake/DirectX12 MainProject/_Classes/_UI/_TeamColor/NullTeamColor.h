/**
 * @file NullTeamColor.h
 * @brief �`�[���J���[��Null�I�u�W�F�N�g�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "TeamColor.h"

class NullTeamColor : public TeamColor {
public:
	NullTeamColor() {}
	virtual ~NullTeamColor() {}

	virtual void LoadAssets() override {}
	virtual void Render(int teamID) override {}
};