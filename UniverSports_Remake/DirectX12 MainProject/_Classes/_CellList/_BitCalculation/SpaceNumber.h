/**
 * @file SpaceNumber.h
 * @brief ��ԕ����ŗp����ԍ��̍\����
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

struct SpaceNumber {
	SpaceNumber operator =(int n) {
		SpaceNumber num;
		num.Level_		= n;
		num.LsIndex_	= n;
		num.MsIndex_	= n;
		return num;
	}

	//! ��ԃ��x��
	int Level_;

	//! �e���x���ł̃C���f�b�N�X
	int LsIndex_;

	//! ���`�l���؂ɂ�����C���f�b�N�X
	int MsIndex_;
};