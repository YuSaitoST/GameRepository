/**
 * @file KeyBoaState.h
 * @brief キーボードの長押し入力クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "KeyBoadBase.h"

class KeyBoadState final : public KeyBoadBase {
public:
	KeyBoadState() {};
	virtual ~KeyBoadState() {};

	virtual void Accepts() override;
};