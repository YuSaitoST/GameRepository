/**
 * @file GameController.h
 * @brief ゲームの進行管理クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Scene.h"
#include "DontDestroyOnLoad.h"
#include "_ControllerState/ControllerState.h"
#include "_AtEndCondition/AtEndCondition.h"

class GameController {
public:
	GameController();
	virtual ~GameController() {}

	GameController(GameController const&) = delete;
	GameController& operator= (GameController const&) = delete;

	void Initialize();
	void LoadAssets();
	NextScene Update(const float deltaTime);
	void Render();
	bool GameFined();

	static bool	gamePlay_;	//! ゲームの進行状態フラグ

private:
	std::unique_ptr<AtEndCondition>		atEndCondition_;	//! 終了条件
	std::unique_ptr<ControllerState>	progress_;			//! 現在のゲーム進行状態
	std::vector<std::unique_ptr<ControllerState>> progressList_;	//! 進行内容のリスト
};