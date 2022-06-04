/**
 * @file PlayersInstructor.h
 * @brief �v���C���[�����N���X
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
class ObjPlayer;

class PlayersInstructor {
public:
	PlayersInstructor() {}
	virtual ~PlayersInstructor() {}

	void Initialize(const std::vector<ObjPlayer*> playerlist);

	ObjPlayer* Access(const int playerID) const;
	ObjPlayer* GetNearestPlayer(DirectX::XMFLOAT2 myPosition);

	DirectX::XMFLOAT2 PlayerHandsPos(const int playerID);

private:
	std::vector<ObjPlayer*> list_;	//! �v���C���[�̃��X�g
	std::vector<DirectX::SimpleMath::Vector2*> posList_;	//! �v���C���[�̍��W���X�g
};