#include "UseKeyCheck.h"

UseKeyCheck UseKeyCheck::inctance_;

void UseKeyCheck::Accepts() {
	key_.Accepts();
	pad_.Accepts(0);
}

bool UseKeyCheck::AnyKey() {
	return key_.EventAnyKey() || pad_.EventAnyKey(0);
}

bool UseKeyCheck::UpKey() {
	return key_.EventOnOffKey(KEY::UP) || pad_.EventOnOffKey(0, PAD::P_UP) || pad_.EventOnOffKey(0, PAD::STICK_L_UP) || pad_.EventOnOffKey(0, PAD::STICK_R_UP);
}

bool UseKeyCheck::DownKey() {
	return key_.EventOnOffKey(KEY::DOWN) || pad_.EventOnOffKey(0, PAD::P_DOWN) || pad_.EventOnOffKey(0, PAD::STICK_L_DOWN) || pad_.EventOnOffKey(0, PAD::STICK_R_DOWN);
}

bool UseKeyCheck::LeftKey() {
	return key_.EventOnOffKey(KEY::LEFT) || pad_.EventOnOffKey(0, PAD::P_LEFT) || pad_.EventOnOffKey(0, PAD::STICK_L_LEFT) || pad_.EventOnOffKey(0, PAD::STICK_R_LEFT);
}

bool UseKeyCheck::RightKey() {
	return key_.EventOnOffKey(KEY::RIGHT) || pad_.EventOnOffKey(0, PAD::P_RIGHT) || pad_.EventOnOffKey(0, PAD::STICK_L_RIGHT) || pad_.EventOnOffKey(0, PAD::STICK_R_RIGHT);
}

bool UseKeyCheck::DecisionKey() {
	return key_.EventOnOffKey(KEY::B) || pad_.EventOnOffKey(0, PAD::P_B);
}

bool UseKeyCheck::CancelKey() {
	return key_.EventOnOffKey(KEY::A) || pad_.EventOnOffKey(0, PAD::P_A);
}

bool UseKeyCheck::AllSelectKey() {
	return key_.EventOnOffKey(KEY::TAB);
}

bool UseKeyCheck::ThrasherKey(int index) {
	return key_.EventOnOffKey(KEY::B) || pad_.StateOnOffKey(0, PAD::P_B);
}

bool UseKeyCheck::ShotKey(int index) {
	return (!index) ? (key_.EventOnOffKey(KEY::S) || pad_.EventOnOffKey(index, PAD::P_A)) : (pad_.EventOnOffKey(index, PAD::P_A));
}

Vector2 UseKeyCheck::MoveDirection(int index) {
	if (index == 0)
		//return (key_.StateDirection() != Vector2::Zero) ? key_.StateDirection() * Vector2(1.0f, -1.0f) : pad_.LeftStateDirection360(index);
		return key_.StateDirection();
	else
		return (pad_.LeftStateDirection360(index));
}