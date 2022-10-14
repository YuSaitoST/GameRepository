/**
 * @file OkMessageBox.h
 * @brief メッセージボックスを表示させる
 * @author 齋藤優宇
 * @date 2021/07/15
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <Windows.h>
#include <string>

namespace YUSTK {
	inline void WINAPI MessageBox_OK(LPCWSTR message, LPCWSTR title) {
		MessageBox(NULL, message, title, MB_OK);
	}
}