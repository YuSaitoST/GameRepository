#include "InputChecker.h"

InputChecker InputChecker::inctance_;

/**
	@brief	キーボードの入力状態を調べる
	@detail 内部はbool配列となっており、1つずつ個別に調べている
			inpEvent_ : 押したかどうか
			inpState_ : 長押しをしているかどうか
*/
void InputChecker::Accepts() {
	inpEvent_.Accepts();
	inpState_.Accepts();
}

/**
	@brief	指定した文字の入力状態を返す
	@param  inputKey  入力状態を調べたい文字を指定する(A～Zの範囲)
	@return　true : 入力された false : 入力されていない
*/
bool InputChecker::EventCharaKey(char inputKey) {
	return inpEvent_.CharaKey(inputKey);
}

/**
	@brief	指定した方向の入力状態を返す
	@param  inputKey  入力状態を調べたい方向を指定する(UP,DOWN,LEFT,RIGHT)
	@return　true : 入力された false : 入力されていない
*/
bool InputChecker::EventArrowKey(ARROW_KEY inputKey) {
	return inpEvent_.ArrowKey(inputKey);
}

/**
	@brief	何かしらの文字か方向の入力状態を返す
	@return　true : 入力された false : 入力されていない
*/
bool InputChecker::EventAnyKey() {
	return inpEvent_.AnyKey();
}

/**
	@brief	指定した文字の入力状態を返す
	@return　入力した方向のベクトル(正規化されている)
*/
Vector2 InputChecker::EventDirection() {
	return inpEvent_.Direction();
}

/**
	@brief	指定した文字の入力状態を返す
	@param  inputKey  入力状態を調べたい文字を指定する(A～Zの範囲)
	@return　true : 入力されている false : 入力されていない
*/
bool InputChecker::StateCharaKey(char inputKey) {
	return inpState_.CharaKey(inputKey);
}

/**
	@brief	指定した方向の入力状態を返す
	@param  inputKey  入力状態を調べたい方向を指定する(UP,DOWN,LEFT,RIGHT)
	@return　true : 入力されている false : 入力されていない
*/
bool InputChecker::StateArrowKey(ARROW_KEY inputKey) {
	return inpState_.ArrowKey(inputKey);
}

/**
	@brief	何かしらの文字か方向の入力状態を返す
	@return　true : 入力されている false : 入力されていない
*/
bool InputChecker::StateAnyKey() {
	return inpState_.AnyKey();
}

/**
	@brief	指定した文字の入力状態を返す
	@return　入力している方向のベクトル(正規化されている)
*/
Vector2 InputChecker::StateDirection() {
	return inpState_.Direction();
}

Vector2 InputChecker::PadEventDirection(int index) {
	return padEvent_.Direction(index);
}

Vector2 InputChecker::PadStateDirection(int index) {
	return padState_.Direction(index);
}