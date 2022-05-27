/**
 * @file LoadCSC.h
 * @brief CSV読み取り処理
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <string>
#include <map>

namespace CSV {
	void Schan(std::wstring fileName, const char* format, ...);
}