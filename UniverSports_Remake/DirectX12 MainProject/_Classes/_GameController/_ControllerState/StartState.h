/**
 * @file StartState.h
 * @brief ���C���J�n���̕`��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
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
	std::unique_ptr<CountTimer>		timer_;		//! �^�C�}�[
	std::unique_ptr<CountDownUI>	countDown_;	//! �J�n�O�J�E���g�_�E��UI
	std::unique_ptr<BlackOut>		blackOut_;	//! �u���b�N�A�E�g

	float startTime_;	//! �Q�[���̐�������
};