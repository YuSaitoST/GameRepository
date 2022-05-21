#include "ActMove.h"
#include "_Classes/_CellList/_Object/_Player/ObjPlayer.h"
#include "_Classes/_CellList/ObjectManager.h"

void ActMove::Update(const float deltaTime, Vector2 direction, ObjPlayer& player) {
	const Vector2 power = direction * GAME_CONST.Move_FirSpeed * deltaTime;
	player.Moving(Vector3(power.x, power.y, 0.0f));
	player.AssignPosition();
}

void ActMove::Update(const float deltaTime, ObjPlayer& player) {
	const Vector2 power = direction_ * GAME_CONST.Move_FirSpeed * deltaTime;
	player.Moving(Vector3(power.x, power.y, 0.0f));
	player.AssignPosition();
}

bool ActMove::Think(ObjPlayer& my) {
	float _comparison = 99.0f;

	ObjectBase* _targetPlayer	= ObjectManager::TheClosestPlayer(my.myObjectID(), my.myPosition(), _comparison);
	ObjectBase* _targetBall		= ObjectManager::TheClosestBall(my.myPosition(), _comparison);

	if (_targetPlayer != nullptr) {
		if (((ObjPlayer*)_targetPlayer)->HasBall()) {
			// ���肪�{�[���������Ă���Ȃ�
			// ��������������߂�
			SeekEscapeDirection(_targetPlayer->myDirection());
			return true;
		}
		else if (my.HasBall()) {
			// ��������������߂�
			SeekForwardDirection(my.myPosition(), _targetPlayer->myPosition());
			return true;
		}
	}
	else if (_targetBall != nullptr) {
		if (((ObjBall*)_targetBall)->GetOwnerID() != -1) {
			// �Ώۂ̃{�[�����u������ꂽ�{�[���v�Ȃ�
			// �����x�N�g���̌��������߂�
			SeekEscapeDirection(_targetBall->myDirection());
			return true;
		}
		else if (my.HasBall() == 0) {
			// �{�[���������Ă��Ȃ��Ȃ�A�{�[�������ɍs��
			SeekForwardDirection(my.myPosition(), _targetBall->myPosition());
			return true;
		}
	}
}

/**
* @brief ����������Ԃ�
* @param targetDirection ����̕���
* @return ���������x�N�g��
*/
Vector2 ActMove::GetVerticalDirection(Vector2 targetsDirection) {
	return Vector2(-targetsDirection.y, targetsDirection.x);
}

/**
* @brief ����������x�N�g�����Z�o����
* @param targetPosition ����̍��W
*/
void ActMove::SeekEscapeDirection(Vector2 targetsDirection) {
	direction_ = GetVerticalDirection(targetsDirection);
	const bool _ImOnTop = (0.0f < direction_.y) && (targetsDirection.y < 0.0f);
	const bool _TargetOnTop = (direction_.y < 0.0f) && (0.0f < targetsDirection.y);
	direction_.y *= (_ImOnTop || _TargetOnTop) ? 1 : -1;
	direction_.Normalize();
}

/**
* @brief �ړ������x�N�g�����Z�o����
* @param myPosition ���g�̍��W
* @param targetPosition ����̍��W
*/
void ActMove::SeekForwardDirection(Vector2 myPosition, Vector2 targetPosition) {
	direction_ = targetPosition - myPosition;
	direction_.Normalize();
}