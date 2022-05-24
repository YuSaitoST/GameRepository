#include "UseKeyCheck.h"

UseKeyCheck UseKeyCheck::inctance_;

/**
* @brief ���͏�Ԃ𒲂ׂ�
*/
void UseKeyCheck::Accepts() {
	key_.Accepts();
	pad_.Accepts(0);
	pad_.Accepts(1);
	pad_.Accepts(2);
	pad_.Accepts(3);
}

/**
* @brief ��������̒P�����͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::AnyKey() {
	return key_.EventAnyKey() || pad_.EventAnyKey(0) || pad_.EventAnyKey(1) || pad_.EventAnyKey(2) || pad_.EventAnyKey(3);
}

/**
* @brief Tab�̒P�����͏�Ԃ��
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::TabKey() {
	return key_.EventOnOffKey(KEY::TAB);
}

/**
* @brief ������̒P�����͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::UpKey(const int index) {
	return key_.EventOnOffKey(KEY::UP) || pad_.EventOnOffKey(index, PAD::P_UP) || pad_.EventOnOffKey(index, PAD::STICK_L_UP);
}

/**
* @brief �������̒P�����͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::DownKey(const int index) {
	return key_.EventOnOffKey(KEY::DOWN) || pad_.EventOnOffKey(index, PAD::P_DOWN) || pad_.EventOnOffKey(index, PAD::STICK_L_DOWN);
}

/**
* @brief �������̒P�����͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::LeftKey(const int index) {
	//�v���C���[0�̏ꍇ�A�L�[�{�[�h���͂ł�����\
	if (index == 0)
		return key_.EventOnOffKey(KEY::LEFT) || pad_.EventOnOffKey(index, PAD::P_LEFT) || pad_.EventOnOffKey(index, PAD::STICK_L_LEFT);
	else
		return pad_.EventOnOffKey(index, PAD::P_LEFT) || pad_.EventOnOffKey(index, PAD::STICK_L_LEFT);
}

/**
* @brief �E�����̒P�����͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::RightKey(const int index) {
	//�v���C���[0�̏ꍇ�A�L�[�{�[�h���͂ł�����\
	if (index == 0)
		return key_.EventOnOffKey(KEY::RIGHT) || pad_.EventOnOffKey(index, PAD::P_RIGHT) || pad_.EventOnOffKey(index, PAD::STICK_L_RIGHT);
	else
		return pad_.EventOnOffKey(index, PAD::P_RIGHT) || pad_.EventOnOffKey(index, PAD::STICK_L_RIGHT);
}

/**
* @brief ����{�^���̒P�����͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::DecisionKey(const int index) {
	return KeyEventB(index);
}

/**
* @brief �L�����Z���{�^���̒P�����͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::CancelKey(const int index) {
	return KeyEventA(index);
}

/**
* @brief �����{�^���̒��������͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::ThrasherKey(const int index) {
	//�v���C���[0�̏ꍇ�A�L�[�{�[�h���͂ł�����\
	if (index == 0)
		return key_.StateOnOffKey(KEY::X) || pad_.StateOnOffKey(index, PAD::P_B);
	else
		return pad_.StateOnOffKey(index, PAD::P_B);
}

/**
* @brief �V���b�g�{�^���̒P�����͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::ShotKey(const int index) {
	return KeyEventA(index);
}

/**
* @brief �ړ��̒��������͕�����Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
Vector2 UseKeyCheck::MoveDirection(const int index) {
	//�v���C���[0�̏ꍇ�A�L�[�{�[�h���͂ł�����\
	if (index == 0)
		return (key_.StateDirection() != Vector2::Zero) ? key_.StateDirection() : pad_.LeftStateDirection360(index);
	else
		return pad_.LeftStateDirection360(index);
}

/**
* @brief �~�j�Q�[���I���{�^���̒P�����͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::MiniGameFinedKey(const int index) {
	return KeyEventB(index);
}

/**
* @brief A�{�^���̒P�����͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::KeyEventA(const int index) {
	//�v���C���[0�̏ꍇ�A�L�[�{�[�h���͂ł�����\
	if (index == 0)
		return key_.EventOnOffKey(KEY::Z) || pad_.EventOnOffKey(index, PAD::P_A);
	else
		return pad_.EventOnOffKey(index, PAD::P_A);
}

/**
* @brief B�{�^���̒P�����͏�Ԃ�Ԃ�
* @return ���͂���Ă����true�@�Ȃ����false
*/
bool UseKeyCheck::KeyEventB(const int index) {
	//�v���C���[0�̏ꍇ�A�L�[�{�[�h���͂ł�����\
	if (index == 0)
		return key_.EventOnOffKey(KEY::X) || pad_.EventOnOffKey(index, PAD::P_B);
	else
		return pad_.EventOnOffKey(index, PAD::P_B);
}