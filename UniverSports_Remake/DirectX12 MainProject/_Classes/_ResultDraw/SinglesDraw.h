/**
 * @file SinglesDraw.h
 * @brief �V���O���X���[�h���̕`��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "DrawingByMode.h"

class SinglesDraw final : public DrawingByMode {
public:
	SinglesDraw() {}
	virtual ~SinglesDraw() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual void Render() override;
};