#include "UseKeyCheck.h"

UseKeyCheck UseKeyCheck::inctance_;

/**
* @brief 入力状態を調べる
*/
void UseKeyCheck::Accepts() {
	key_.Accepts();
	pad_.Accepts(0);
	pad_.Accepts(1);
	pad_.Accepts(2);
	pad_.Accepts(3);
}

/**
* @brief 何かしらの単発入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::AnyKey() {
	return key_.EventAnyKey() || pad_.EventAnyKey(0) || pad_.EventAnyKey(1) || pad_.EventAnyKey(2) || pad_.EventAnyKey(3);
}

/**
* @brief Tabの単発入力状態を返
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::TabKey() {
	return key_.EventOnOffKey(KEY::TAB);
}

/**
* @brief 上方向の単発入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::UpKey(const int index) {
	return key_.EventOnOffKey(KEY::UP) || pad_.EventOnOffKey(index, PAD::P_UP) || pad_.EventOnOffKey(index, PAD::STICK_L_UP);
}

/**
* @brief 下方向の単発入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::DownKey(const int index) {
	return key_.EventOnOffKey(KEY::DOWN) || pad_.EventOnOffKey(index, PAD::P_DOWN) || pad_.EventOnOffKey(index, PAD::STICK_L_DOWN);
}

/**
* @brief 左方向の単発入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::LeftKey(const int index) {
	//プレイヤー0の場合、キーボード入力でも操作可能
	if (index == 0)
		return key_.EventOnOffKey(KEY::LEFT) || pad_.EventOnOffKey(index, PAD::P_LEFT) || pad_.EventOnOffKey(index, PAD::STICK_L_LEFT);
	else
		return pad_.EventOnOffKey(index, PAD::P_LEFT) || pad_.EventOnOffKey(index, PAD::STICK_L_LEFT);
}

/**
* @brief 右方向の単発入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::RightKey(const int index) {
	//プレイヤー0の場合、キーボード入力でも操作可能
	if (index == 0)
		return key_.EventOnOffKey(KEY::RIGHT) || pad_.EventOnOffKey(index, PAD::P_RIGHT) || pad_.EventOnOffKey(index, PAD::STICK_L_RIGHT);
	else
		return pad_.EventOnOffKey(index, PAD::P_RIGHT) || pad_.EventOnOffKey(index, PAD::STICK_L_RIGHT);
}

/**
* @brief 決定ボタンの単発入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::DecisionKey(const int index) {
	return KeyEventB(index);
}

/**
* @brief キャンセルボタンの単発入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::CancelKey(const int index) {
	return KeyEventA(index);
}

/**
* @brief 加速ボタンの長押し入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::ThrasherKey(const int index) {
	//プレイヤー0の場合、キーボード入力でも操作可能
	if (index == 0)
		return key_.StateOnOffKey(KEY::X) || pad_.StateOnOffKey(index, PAD::P_B);
	else
		return pad_.StateOnOffKey(index, PAD::P_B);
}

/**
* @brief ショットボタンの単発入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::ShotKey(const int index) {
	return KeyEventA(index);
}

/**
* @brief 移動の長押し入力方向を返す
* @return 入力されていればtrue　なければfalse
*/
Vector2 UseKeyCheck::MoveDirection(const int index) {
	//プレイヤー0の場合、キーボード入力でも操作可能
	if (index == 0)
		return (key_.StateDirection() != Vector2::Zero) ? key_.StateDirection() : pad_.LeftStateDirection360(index);
	else
		return pad_.LeftStateDirection360(index);
}

/**
* @brief ミニゲーム終了ボタンの単発入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::MiniGameFinedKey(const int index) {
	return KeyEventB(index);
}

/**
* @brief Aボタンの単発入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::KeyEventA(const int index) {
	//プレイヤー0の場合、キーボード入力でも操作可能
	if (index == 0)
		return key_.EventOnOffKey(KEY::Z) || pad_.EventOnOffKey(index, PAD::P_A);
	else
		return pad_.EventOnOffKey(index, PAD::P_A);
}

/**
* @brief Bボタンの単発入力状態を返す
* @return 入力されていればtrue　なければfalse
*/
bool UseKeyCheck::KeyEventB(const int index) {
	//プレイヤー0の場合、キーボード入力でも操作可能
	if (index == 0)
		return key_.EventOnOffKey(KEY::X) || pad_.EventOnOffKey(index, PAD::P_B);
	else
		return pad_.EventOnOffKey(index, PAD::P_B);
}