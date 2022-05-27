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
#include "_Classes/_UI/_CountTimer/CountTimer.h"
#include "_Classes/_UI/_CountDown/CountDown.h"
#include "_Classes/_UI/_BlackOut/BlackOut.h"
#include "_Classes/_UI/_Finish/Finish.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"

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

	static bool GamePlay() { return gameStart_; }

private:
	int RemainingNumberOfPlayer();
	int RemainingOfTeam();

	const float TIME_COUNT		= 4.2f;
	const float TIME_LIMIT[4]	= { 0.0f, 0.0f, 120.0f, 0.0f };
	const float	SPEED_FADE[3]	= { 51.0f, 510.0f, 0.0f };

	//! �^�C�}�[
	std::unique_ptr<CountTimer> timer_;

	//! �J�n�O�J�E���g�_�E��
	std::unique_ptr<CountDownUI> countDown_;

	//! �u���b�N�A�E�g
	std::unique_ptr<BlackOut> blackOut_;

	//! �I�����e�L�X�g
	std::unique_ptr<Finish> ui_finish_;

	//! �I����SE
	std::unique_ptr<SoundPlayer> se_whistle_;

	//! �Q�[���̐�������
	float			startTime_;

	//! �Q�[���̐i�s��ԃt���O
	static bool		gameStart_;
};