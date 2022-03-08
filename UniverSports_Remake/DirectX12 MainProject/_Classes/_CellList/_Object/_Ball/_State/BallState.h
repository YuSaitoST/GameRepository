#pragma once

class ObjBall;

class BallState {
public:
	BallState() {}
	virtual ~BallState() {}

	virtual void Initialize() = 0;
	virtual void Update(const float deltaTime, ObjBall* ball) = 0;
};

/*
	[��Ԃ̎��]

	<���ʍ���>

	<���ፀ��>
	�E���V : �����_����{���W,����}�̊m��A
			 ���߂��ʒu��ball->pos_�ɑ��(ObjBall.Render�ŃZ�b�g�����)
	�E�ߊl : 
	�E���� : 
*/