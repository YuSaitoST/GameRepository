#include "UseKeyCheck.h"

UseKeyCheck UseKeyCheck::inctance_;

void UseKeyCheck::Accepts() {
	key_.Accepts();
	pad_.Accepts(0);
	pad_.Accepts(1);
	pad_.Accepts(2);
	pad_.Accepts(3);
}

bool UseKeyCheck::AnyKey() {
	return key_.EventAnyKey() || pad_.EventAnyKey(0) || pad_.EventAnyKey(1) || pad_.EventAnyKey(2) || pad_.EventAnyKey(3);
}

bool UseKeyCheck::TabKey() {
	return key_.EventOnOffKey(KEY::TAB);
}

bool UseKeyCheck::UpKey(const int index) {
	return key_.EventOnOffKey(KEY::UP) || pad_.EventOnOffKey(index, PAD::P_UP) || pad_.EventOnOffKey(index, PAD::STICK_L_UP);
}

bool UseKeyCheck::DownKey(const int index) {
	return key_.EventOnOffKey(KEY::DOWN) || pad_.EventOnOffKey(index, PAD::P_DOWN) || pad_.EventOnOffKey(index, PAD::STICK_L_DOWN);
}

bool UseKeyCheck::LeftKey(const int index) {
	if (index == 0)
		return key_.EventOnOffKey(KEY::LEFT) || pad_.EventOnOffKey(index, PAD::P_LEFT) || pad_.EventOnOffKey(index, PAD::STICK_L_LEFT);
	else
		return pad_.EventOnOffKey(index, PAD::P_LEFT) || pad_.EventOnOffKey(index, PAD::STICK_L_LEFT);
}

bool UseKeyCheck::RightKey(const int index) {
	if (index == 0)
		return key_.EventOnOffKey(KEY::RIGHT) || pad_.EventOnOffKey(index, PAD::P_RIGHT) || pad_.EventOnOffKey(index, PAD::STICK_L_RIGHT);
	else
		return pad_.EventOnOffKey(index, PAD::P_RIGHT) || pad_.EventOnOffKey(index, PAD::STICK_L_RIGHT);
}

bool UseKeyCheck::DecisionKey(const int index) {
	return KeyEventB(index);
}

bool UseKeyCheck::CancelKey(const int index) {
	return KeyEventA(index);
}

bool UseKeyCheck::ThrasherKey(const int index) {
	if (index == 0)
		return key_.StateOnOffKey(KEY::B) || pad_.StateOnOffKey(index, PAD::P_B);
	else
		return pad_.StateOnOffKey(index, PAD::P_B);
}

bool UseKeyCheck::ShotKey(const int index) {
	return KeyEventA(index);
}

Vector2 UseKeyCheck::MoveDirection(const int index) {
	if (index == 0)
		return (key_.StateDirection() != Vector2::Zero) ? key_.StateDirection() : pad_.LeftStateDirection360(index);
	else
		return pad_.LeftStateDirection360(index);
}

bool UseKeyCheck::MinGameFinedKey(const int index) {
	return KeyEventB(index);
}

bool UseKeyCheck::KeyEventA(const int index) {
	if (index == 0)
		return key_.EventOnOffKey(KEY::A) || pad_.StateOnOffKey(index, PAD::P_A);
	else
		return pad_.StateOnOffKey(index, PAD::P_A);
}

bool UseKeyCheck::KeyEventB(const int index) {
	if (index == 0)
		return key_.EventOnOffKey(KEY::B) || pad_.StateOnOffKey(index, PAD::P_B);
	else
		return pad_.StateOnOffKey(index, PAD::P_B);
}