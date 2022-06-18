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
	//! ������
	const int NumberOfDivisions = 4;

	//! ��������i�K��
	const int DivisionLevel = 2;

	int BitSlide(int bit);
	int PointToMorton(DirectX::XMFLOAT2 pos);
	void MoverToMorton(DirectX::XMFLOAT2 m_pos, float radian, SpaceNumber& numbers);

	/**
	* @brief ��ԃ��x���ƃ��x�����̃C���f�b�N�X���烂�[�g�����������߂�(���䋉��)
	* @param Level ��ԃ��x��
	* @param Index ���x�����̃C���f�b�N�X
	* @return ���[�g������
	*/
	inline int GetIndex(int Level, int Index) {
		return (((std::pow(NumberOfDivisions, Level) - 1) / (NumberOfDivisions - 1)) + Index);
	}

}  //namespace BitCalculation