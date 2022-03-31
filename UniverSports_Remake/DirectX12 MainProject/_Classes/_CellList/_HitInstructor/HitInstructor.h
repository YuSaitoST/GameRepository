#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class HitInstructor {
public:
	HitInstructor() {}
	virtual ~HitInstructor() {}

	static void BallCautch(const int playerID, const int ballID);
	static void BallShot(const int ballID, DirectX::SimpleMath::Vector2 forward);
	static void BallBreak(const int ballID);
};

/*
	[�ړI]
	�Z�ȉ��̏󋵂ɂȂ����ۂɑ��葤�ɒʒm����
		�EPlayer���u����Ball�v���L���b�`������
		�EPlayer���u����Ball�v�ɂԂ�������
		�EPlayer��Wire����{�[�����m�ۂ��鎞
		�EBall��Wire�ɓ�������
	�ZBall��Wire���󂯐g�ɂ���
		-> ��ԕ����ɂ��A�悯���Ȕ�������炷

	[�g�p�C���[�W]
	�E���Player�������ɂԂ������ۂɊ֐����Ăяo��
		HitInstructor::BallCautch();

	[�������e]
	(�D��x��)
	�EPlayer���u����Ball�v���L���b�`������
		-> Ball) ���ꂽ����ɂ���
	�EPlayer���u����Ball�v�ɂԂ�������
		-> Ball) isBreak_��true�ɂ���
	(�D��x��)
	�EPlayer��Wire����{�[�����m�ۂ��鎞
	�EWire��Ball����������(���[�v�񐔌��点��(Wire�ŌĂԂ�*4��ABall�ŌĂԂƍŒ�*5��))
*/