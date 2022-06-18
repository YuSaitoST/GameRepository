/**
 * @file StartState.h
 * @brief メイン開始時の描画クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "ControllerState.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"
#include "_Classes/_UI/_CountDown/CountDown.h"
#include "_Classes/_UI/_BlackOut/BlackOut.h"

class StartState : public ControllerState {
public:
	StartState();
	virtual ~StartState() {}

	virtual void Initialize() override;
	virtual void LoadAsstes() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() override;

	virtual bool ChangeDrawing(GameController* controller) override;
	virtual CountTimer* GetTimer() override { return nullptr; }

private:
	std::unique_ptr<CountTimer>		timer_;		//! タイマー
	std::unique_ptr<CountDownUI>	countDown_;	//! 開始前カウントダウンUI
	std::unique_ptr<BlackOut>		blackOut_;	//! ブラックアウト

	float startTime_;	//! ゲームの制限時間
};