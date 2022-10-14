/**
 * @file DemoDisplay.h
 * @brief タイトルのデモプレイ表示クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "DisplayBase.h"
#include "_Classes/_MoviePlayer/MoviePlayer.h"

class DemoDisplay final : public DisplayBase {
public:
	DemoDisplay() { movie_ = std::make_unique<MoviePlayer>(); }
	virtual ~DemoDisplay() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual NextScene Update(const float deltaTime) override;
	virtual void Render() override;
	virtual void Reset() override;
	virtual DISPLAYMODE IsChange() override;
	virtual void ReDisplayInitialize() override;

private:
	std::unique_ptr<MoviePlayer> movie_;	//! 背景動画
};