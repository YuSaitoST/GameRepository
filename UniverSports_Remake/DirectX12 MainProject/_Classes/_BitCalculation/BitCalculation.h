/**
 * @file BitCalculation.h
 * @brief �r�b�g�v�Z
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

namespace BitCalculation {
	int BitSlide(int bit);
	int PointToMorton(DirectX::XMFLOAT2 pos);
	int GetIndex(int Level, int Index);
	const int NumberOfDivisions = 4;
	const int DivisionLevel = 2;
}  //namespace BitCalculation