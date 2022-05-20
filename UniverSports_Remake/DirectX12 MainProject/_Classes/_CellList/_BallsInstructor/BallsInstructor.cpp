#include "BallsInstructor.h"
#include "_Classes/_CellList/ObjectManager.h"

/**
* @brief �L���b�`�w��
*/
void BallsInstructor::BallCautch(const int playerID, const int ballID) {
	ObjectManager::Access(ballID)->WasCaught(playerID);
}

/**
* @brief �����w��
*/
void BallsInstructor::BallShot(const int ballID, DirectX::SimpleMath::Vector2 forward) {
	ObjectManager::Access(ballID)->WasThrown(forward);
}

/**
* @brief ������ꂽ�{�[���̍폜�w��
*/
void BallsInstructor::BallBreakOfThrower(const int ballID) {
	ObjectManager::Access(ballID)->WasGuessed();
}

/**
* @brief ��������Ă�{�[���̍폜�w��
*/
void BallsInstructor::BallBreakOfTheHitter(const int ballID) {
	ObjectManager::Access(ballID)->BallBreak();
}