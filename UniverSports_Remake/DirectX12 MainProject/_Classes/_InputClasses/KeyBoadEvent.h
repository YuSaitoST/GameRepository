/**
 * @file KeyBoadEvent.h
 * @brief キーボードの単発入力クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "KeyBoadBase.h"

class KeyBoadEvent final : public KeyBoadBase {
public:
	KeyBoadEvent() {};
	virtual ~KeyBoadEvent() {};

	virtual void Accepts() override;
};