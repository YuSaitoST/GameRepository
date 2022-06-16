/**
 * @file ControllerState.h
 * @brief �Q�[���i�s�̏�Ԋ��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

//�O���錾
class GameController;
class CountTimer;

class ControllerState {
public:
	ControllerState() {}
	virtual ~ControllerState() {}

	virtual void Initialize() = 0;
	virtual void LoadAsstes() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() = 0;

	virtual bool ChangeDrawing(GameController* controller) = 0;
	virtual CountTimer* GetTimer() = 0;
};