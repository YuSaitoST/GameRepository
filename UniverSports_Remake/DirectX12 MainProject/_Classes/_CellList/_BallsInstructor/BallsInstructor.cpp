#include "BallsInstructor.h"
#include "_Classes/_CellList/_Object/_Ball/BallList.h"

/**
* @brief �L���b�`�w��
*/
void BallsInstructor::Cautch(const int playerID, const int ballID) {
	list_[ballID]->WasCaught(playerID);
}

/**
* @brief �����w��
*/
void BallsInstructor::Shot(const int ballID, DirectX::SimpleMath::Vector2 forward) {
	list_[ballID]->WasThrown(forward);
}

/**
* @brief ������ꂽ�{�[���̍폜�w��
*/
void BallsInstructor::BreakOfThrower(const int ballID) {
	list_[ballID]->WasGuessed();
}

/**
* @brief ��������Ă�{�[���̍폜�w��
*/
void BallsInstructor::BreakOfTheHitter(const int ballID) {
	list_[ballID]->BallBreak();
}