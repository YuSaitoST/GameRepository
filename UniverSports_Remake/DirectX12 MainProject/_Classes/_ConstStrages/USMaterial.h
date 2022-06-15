/**
 * @file USMaterial.h
 * @brief �}�e���A���p�̐F
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"

namespace USMaterial {
	//! �v���C���[�ɍ������f�B�t���[�Y�F
	const D3DCOLORVALUE P_DIFFUSE[5] = {
		D3DCOLORVALUE(0.0f,0.65f,0.0f,1.0f),	// ��(PL.1)
		D3DCOLORVALUE(0.65f,0.0f,0.65f,1.0f),	// ��(PL.2)
		D3DCOLORVALUE(0.65f,0.0f,0.0f,1.0f),	// ��(PL.3)
		D3DCOLORVALUE(0.0f,0.0f,0.65f,1.0f),	// ��(PL.4)
		D3DCOLORVALUE(0.0f,0.0f,0.0f,0.0f)
	};
	//! �A���r�G���g�F
	const D3DCOLORVALUE P_AMBIENT = D3DCOLORVALUE(0.35f, 0.35f, 0.35f, 1.0f);

}	//namespace USMaterial