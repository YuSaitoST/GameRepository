/**
 * @file PlayState.h
 * @brief メインプレイ中の描画クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "ControllerState.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

class PlayState : public ControllerState {
public:
	PlayState();
	virtual ~PlayState() {}

	virtual void Initialize() override;
	virtual void LoadAsstes() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() override;

	virtual bool ChangeDrawing(GameController* controller) override;
	virtual CountTimer* GetTimer() override { return timer_.get(); }

private:
	const float TIME_LIMIT[4] = { 0.0f, 0.0f, 120.0f, 0.0f };

	std::unique_ptr<CountTimer> timer_;	//! タイマー
	DX9::SPRITEFONT				font_;	//! フォント
};