/**
 * @file FinishState.h
 * @brief メイン終了時の描画クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "ControllerState.h"
#include "_Classes/_UI/_Finish/Finish.h"
#include "_Classes/_UI/_BlackOut/BlackOut.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"

class FinishState : public ControllerState {
public:
	FinishState();
	virtual ~FinishState() {}

	virtual void Initialize() override;
	virtual void LoadAsstes() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() override;

	virtual bool ChangeDrawing(GameController* controller) override;
	virtual CountTimer* GetTimer()override { return nullptr; }

private:
	const float	SPEED_FADE = 51.0f;

	std::unique_ptr<Finish>			ui_finish_;		//! 終了時テキスト
	std::unique_ptr<BlackOut>		blackOut_;		//! ブラックアウト
	std::unique_ptr<SoundPlayer>	se_whistle_;	//! 終了時SE
};