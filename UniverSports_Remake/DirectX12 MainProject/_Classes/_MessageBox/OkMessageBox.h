/**
 * @file OkMessageBox.h
 * @brief ���b�Z�[�W�{�b�N�X��\��������
 * @author �V���D�F
 * @date 2021/07/15
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <Windows.h>
#include <string>

namespace YUSTK {
	inline void WINAPI MessageBox_OK(LPCWSTR message, LPCWSTR title) {
		MessageBox(NULL, message, title, MB_OK);
	}
}