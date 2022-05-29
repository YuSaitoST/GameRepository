#include "BallsInstructor.h"
#include "_Classes/_CellList/_Object/_Ball/BallList.h"
#include "_Classes/_NearestPosition/NearestPosition.h"

void BallsInstructor::Initialize() {
	for (ObjBall* ball : list_)
		posList_.push_back(&(ball->myPosition()));
}

/**
* @brief �A�N�Z�X����
* @param ballID �{�[����ID
* @return �{�[��
*/
ObjBall* BallsInstructor::Access(const int ballID) const {
	if (ballID < 0)
		return nullptr;

	return list_[ballID];
}

/**
* @brief �L���b�`�w��
* @param playerID �v���C���[��ID
* @param ballID �{�[����ID
*/
void BallsInstructor::Cautch(const int playerID, const int ballID) {
	list_[ballID]->WasCaught(playerID);
}

/**
* @brief �����w��
* @param ballID �{�[����ID
*/
void BallsInstructor::Shot(const int ballID, DirectX::SimpleMath::Vector2 forward) {
	list_[ballID]->WasThrown(forward);
}

/**
* @brief ������ꂽ�{�[���̍폜�w��
* @param ballID �{�[����ID
*/
void BallsInstructor::BreakOfThrower(const int ballID) {
	list_[ballID]->WasGuessed();
}

/**
* @brief ��������Ă�{�[���̍폜�w��
* @param ballID �{�[����ID
*/
void BallsInstructor::BreakOfTheHitter(const int ballID) {
	list_[ballID]->BallBreak();
}

/**
* @brief ��ԋ߂��{�[����Ԃ�
* @param myPosition ���g�̍��W
* @return ��ԋ߂��{�[��
*/
ObjBall* BallsInstructor::GetNearestBall(DirectX::XMFLOAT2 myPosition) {
	return Access(PosCheck::GetNearestObjectID(posList_, myPosition));
}