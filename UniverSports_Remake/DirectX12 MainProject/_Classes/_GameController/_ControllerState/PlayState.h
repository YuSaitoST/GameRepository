/**
 * @file PlayState.h
 * @brief ���C���v���C���̕`��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
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

	std::unique_ptr<CountTimer> timer_;	//! �^�C�}�[
	DX9::SPRITEFONT				font_;	//! �t�H���g
};