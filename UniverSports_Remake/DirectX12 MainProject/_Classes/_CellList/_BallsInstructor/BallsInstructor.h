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

//�O���錾
class ObjBall;

class BallsInstructor {
public:
	BallsInstructor() {}
	virtual ~BallsInstructor() {}

	void SetList(const std::vector<ObjBall*>& balllist) { list_ = balllist; }

	void Cautch(const int playerID, const int ballID);
	void Shot(const int ballID, DirectX::SimpleMath::Vector2 forwrad);
	void BreakOfThrower(const int ballID);
	void BreakOfTheHitter(const int ballID);

private:
	//! �{�[���̃��X�g
	std::vector<ObjBall*> list_;
};