/**
 * @file BallsInstructor.h
 * @brief �{�[�������N���X
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

	void Initialize(const std::vector<ObjBall*> balllist);

	ObjBall* Access(const int ballID) const;
	ObjBall* GetNearestBall(DirectX::XMFLOAT2 myPosition);
	void Cautch(const int playerID, const int ballID);
	void Shot(const int ballID, DirectX::SimpleMath::Vector2 forwrad);
	void BreakOfThrower(const int ballID);
	void BreakOfTheHitter(const int ballID);

private:
	std::vector<ObjBall*> list_;	//! �{�[���̃��X�g
	std::vector<DirectX::SimpleMath::Vector2*> posList_;	//! �{�[���̍��W���X�g
};