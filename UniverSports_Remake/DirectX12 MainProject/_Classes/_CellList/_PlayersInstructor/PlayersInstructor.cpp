#include "PlayersInstructor.h"
#include "_Classes/_CellList/_Object/_Player/PlayerList.h"
#include "_Classes/_NearestPosition/NearestPosition.h"

void PlayersInstructor::Initialize(const std::vector<ObjPlayer*> playerlist) {
	list_ = playerlist;

	posList_.reserve(list_.size());

	for (ObjPlayer* player : list_)
		posList_.push_back(&(player->myPosition()));
}

/**
* @brief �A�N�Z�X����
* @param playerID �v���C���[��ID
* @return �{�[��
*/
ObjPlayer* PlayersInstructor::Access(const int playerID) const {
	if (playerID < 0)
		return nullptr;

	return list_[playerID];
}

/**
* @brief ��ԋ߂��v���C���[��Ԃ�
* @param myPosition ���g�̍��W
* @return ��ԋ߂��{�[��
*/
ObjPlayer* PlayersInstructor::GetNearestPlayer(DirectX::XMFLOAT2 myPosition) {
	return Access(PosCheck::GetNearestObjectID(posList_, myPosition));
}

///**
//* @brief �w�肵���v���C���[�̎茳�̍��W��Ԃ�
//* @param index �v���C���[�̔ԍ�
//* @return �茳�̍��W
//*/
//DirectX::XMFLOAT2 PlayersInstructor::PlayerHandsPos(const int playerID) {
//	assert((0 <= playerID) && "PlayerInstructor::PlayerHandPos() : �w�肵��index���s���ł�(���̒l�ɂȂ��Ă���)");
//	return list_[playerID]->Get_HandPos();
//}