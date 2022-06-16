/**
 * @file GameController.h
 * @brief �Q�[���̐i�s�Ǘ��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
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

	static bool	gamePlay_;	//! �Q�[���̐i�s��ԃt���O

private:
	std::unique_ptr<AtEndCondition>		atEndCondition_;	//! �I������
	std::unique_ptr<ControllerState>	progress_;			//! ���݂̃Q�[���i�s���
	std::vector<std::unique_ptr<ControllerState>> progressList_;	//! �i�s���e�̃��X�g
};