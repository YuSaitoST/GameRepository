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
#include "_Classes/_MoviePlayer/MoviePlayer.h"

/***
 * @enum DISPLAYMODE
 * @brief 表示状態
*/
enum DISPLAYMODE { DISPLAY_NORMAL, DISPLAY_DEMO };

class DisplayBase {
public:
	DisplayBase() { movie_ = std::make_unique<MoviePlayer>(); }
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

	virtual bool IsChange() = 0;

	/**
	 * @brief 動画を再生させる
	*/
	virtual void MVPlay() { movie_->Play(); }

protected:
	std::unique_ptr<MoviePlayer> movie_;	//! 背景動画
};