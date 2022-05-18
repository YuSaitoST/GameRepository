/**
 * @file DoublesDraw.h
 * @brief �_�u���X���[�h���̕`��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "DrawingByMode.h"

class DoublesDraw final : public DrawingByMode {
public:
	DoublesDraw() {}
	virtual ~DoublesDraw() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual void Render() override;
};