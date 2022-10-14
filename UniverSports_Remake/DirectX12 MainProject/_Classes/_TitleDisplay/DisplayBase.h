/**
 * @file DisplayBase.h
 * @brief 画面表示の切り替えの基底クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "NextScene.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_InputManager/UseKeyChecker.h"

/***
 * @enum DISPLAYMODE
 * @brief 表示状態
*/
enum DISPLAYMODE { 
	DISPLAY_NORMAL,		// 通常画面
	DISPLAY_DEMO,		// デモプレイ
	DISPLAY_CONFIG,		// 設定画面
	DISPLAY_NONE
};

class DisplayBase {
public:
	DisplayBase() {}
	virtual ~DisplayBase() {}

	DisplayBase(DisplayBase&&) = delete;
	DisplayBase& operator= (DisplayBase&&) = delete;

	DisplayBase(DisplayBase const&) = delete;
	DisplayBase& operator= (DisplayBase const&) = delete;

	virtual void Initialize() = 0;
	virtual void LoadAssets() = 0;
	virtual NextScene Update(const float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Reset() = 0;

	virtual DISPLAYMODE IsChange() = 0;
	virtual void ReDisplayInitialize() = 0;
};