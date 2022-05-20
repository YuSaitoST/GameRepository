/**
 * @file BallsInstructor.h
 * @brief �{�[���̏�ԕω��̎w���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class BallsInstructor {
public:
	BallsInstructor() {}
	virtual ~BallsInstructor() {}

	static void BallCautch(const int playerID, const int ballID);
	static void BallShot(const int ballID, DirectX::SimpleMath::Vector2 forward);
	static void BallBreakOfThrower(const int ballID);
	static void BallBreakOfTheHitter(const int ballID);
};