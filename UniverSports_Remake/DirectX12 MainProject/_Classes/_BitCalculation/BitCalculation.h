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
#include "SpaceNumber.h"

namespace BitCalculation {
	int BitSlide(int bit);
	int PointToMorton(DirectX::XMFLOAT2 pos);
	int GetIndex(int Level, int Index);
	void MoverToMorton(DirectX::XMFLOAT2 m_pos, float radian, SpaceNumber& numbers);

	//! ������
	const int NumberOfDivisions = 4;

	//! ��������i�K��
	const int DivisionLevel = 2;

}  //namespace BitCalculation