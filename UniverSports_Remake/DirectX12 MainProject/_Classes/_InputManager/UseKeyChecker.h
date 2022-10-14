/**
 * @file UseKeyChecker.h
 * @brief ゲームで用いる入力を管理するクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "UseKBKey.h"
#include "UseGPKey.h"
#include "UseVPKey.h"
#include "_Classes/_VPServer/VPManager.h"
#include "_Classes/_MessageBox/OkMessageBox.h"

//マクロ
#define INPSystem UseKeyChecker::GetInstance()

enum class InputSystem {
	KEYBOAD,
	GAMEPAD,
	VIRTUAL_PAD,
	COM,
	NONE
};

class UseKeyChecker {
public:
	static UseKeyChecker& GetInstance() { 
		if (instance_ == nullptr) {
			instance_ = new UseKeyChecker();
		}
		return *instance_; 
	}

	/*
	* @brief 入力方法の変更
	*/
	inline void SetInputSystem(InputSystem system, int playerID) {
		if (system == InputSystem::KEYBOAD) {
			std::vector<InputSystem>::iterator _vecBegin	= inputSystemList_.begin();
			std::vector<InputSystem>::iterator _vecEnd		= inputSystemList_.end();
			std::vector<InputSystem>::iterator _find		= std::find(_vecBegin, _vecEnd, system);

			// 他にキーボードが選択されていたら
			if (_find != _vecEnd) {
				const int _index = _find - _vecBegin;

				// 今回選択したプレイヤーが、以前選択されていたプレイヤーより若いなら
				if (playerID < _index) {
					inputSystemList_[playerID]	= system;
					inputSystemList_[_index]	= InputSystem::COM;
					return;
				}

				// 後ろなら、若い方と入れ替える
				InputSystem _before			= inputSystemList_[_index];
				inputSystemList_[_index]	= inputSystemList_[playerID];
				inputSystemList_[playerID]	= _before;

				if (_before == InputSystem::VIRTUAL_PAD) {
					VPConnection(playerID);
				}

				return;
			}

			inputSystemList_[playerID] = system;
			return;
		}
		else if (system == InputSystem::GAMEPAD) {
			inputSystemList_[playerID] = system;

			// 要素の分だけループさせる
			int _count = 0;
			for (int i = 4 - 1; 0 <= i; --i) {
				if (inputSystemList_[i] != InputSystem::GAMEPAD) {
					continue;
				}

				// 繰り返し入れ替える
				for (int j = 4 - 1; 0 < j; --j) {
					if (inputSystemList_[j - 1] != InputSystem::GAMEPAD) {
						std::swap(inputSystemList_[j], inputSystemList_[j - 1]);
						++_count;
					}
				}
			}

			// 再接続
			for (int i = 0; i < 4; ++i) {
				if (inputSystemList_[i] == InputSystem::VIRTUAL_PAD) {
					VPConnection(i);
				}
			}

			return;
		}
		else if (system == InputSystem::VIRTUAL_PAD) {
			VPConnection(playerID);
		}
		
		// COMなら
		inputSystemList_[playerID] = system;
	}

	/*
	* @brief 全プレイヤーの入力方法をセットする
	*/
	inline void AllInputSystemSetter() {
		for (int i = 0; i < 4; ++i) {
			switch (inputSystemList_[i]) {
				case InputSystem::KEYBOAD		:inputList_[i] = std::make_unique<UseKBKey>();	break;
				case InputSystem::GAMEPAD		:inputList_[i] = std::make_unique<UseGPKey>();	break;
				case InputSystem::VIRTUAL_PAD	:inputList_[i] = std::make_unique<UseVPKey>();	break;
				default							:inputList_[i] = std::make_unique<NoneUseKey>();
			}
		}
	}

	/*
	* @brief 各プレイヤーの入力方法の取得
	*/
	inline std::vector<InputSystem> GetNowInputSystem() const { 
		return inputSystemList_; 
	}

	/*
	* @brief UDP通信の開始
	*/
	inline void UDPStart() {
		vpManager_->UDP_Initialize();
	}

	/*
	* @brief IPアドレスを取得する
	* @return IPアドレス
	*/
	inline std::wstring GetIPAddress() { 
		return ipAddress_;
	}

	/*
	* @brief 各プレイヤーの入力状態を調べる
	*/
	inline void Accepts() {
		VPInput::VPInpSet _input;
		for (int i = 0; i < 4; ++i) {
			inputList_[i]->Accepts(i);

			_input = VPInput::GetInputData(vpManager_->UDP_Receive());
			inputList_[_input.ID]->SetInputFlag(_input);
		}
	}

	inline bool AnyKey() {
		return inputList_[0]->AnyKey() || inputList_[1]->AnyKey() || inputList_[2]->AnyKey() || inputList_[3]->AnyKey();
	}

	inline bool UpKey(const int index) {
		return inputList_[index]->UpKey(index);
	}

	inline bool UpKeyboard() {
		return DXTK->KeyEvent->pressed.Up;
	}

	inline bool DownKey(const int index) {
		return inputList_[index]->DownKey(index);
	}

	inline bool DownKeyboard() {
		return DXTK->KeyEvent->pressed.Down;
	}

	inline bool LeftKey(const int index) {
		return inputList_[index]->LeftKey(index);
	}

	inline bool LeftKeyboard() {
		return DXTK->KeyEvent->pressed.Left;
	}

	inline bool RightKey(const int index) {
		return inputList_[index]->RightKey(index);
	}

	inline bool RightKeyboard() {
		return DXTK->KeyEvent->pressed.Right;
	}

	inline bool DecisionKey(const int index) {
		return inputList_[index]->DecisionKey(index);
	}

	inline bool DecisionKeyboard() {
		return DXTK->KeyEvent->pressed.B;
	}

	inline bool CancelKey(const int index) {
		return inputList_[index]->CancelKey(index);
	}

	inline bool CancelKeyboard() {
		return DXTK->KeyEvent->pressed.A;
	}

	//bool MiniGameFinedKey(const int index);

	inline bool ThrasherKey(const int index) {
		return inputList_[index]->ThrasherKey(index);
	}

	inline bool ShotKey(const int index) {
		return inputList_[index]->ShotKey(index);
	}

	inline Vector2 MoveDirection(const int index) {
		return inputList_[index]->MoveDirection(index);
	}

	/**
	* @brief Tabの単発入力状態を返
	* @return 入力されていればtrue　なければfalse
	*/
	inline bool TabKey() { return DXTK->KeyEvent->pressed.Tab; }

private:
	UseKeyChecker() {
		inputList_.push_back(std::make_unique<UseKBKey>());
		inputList_.push_back(std::make_unique<UseGPKey>());
		inputList_.push_back(std::make_unique<UseGPKey>());
		inputList_.push_back(std::make_unique<UseGPKey>());

		inputSystemList_.push_back(InputSystem::KEYBOAD);
		inputSystemList_.push_back(InputSystem::COM);
		inputSystemList_.push_back(InputSystem::COM);
		inputSystemList_.push_back(InputSystem::COM);

		vpManager_ = std::make_unique<VPManager>();
		
		std::string ipAddr = vpManager_->GetIPAddress();
		
		std::vector<wchar_t> dest(ipAddr.length() + 16);
		std::size_t converted;
		::mbstowcs_s(&converted, dest.data(), dest.size(), ipAddr.c_str(), _TRUNCATE);
		ipAddress_ = std::wstring(dest.data());
	}
	virtual ~UseKeyChecker() {}

	/*
	* @brief VirtualPadの接続
	* @param playerID プレイヤーのID
	* @return 接続の成功
	*/
	inline bool VPConnection(int playerID) {		
		std::wstring	_wstr		= std::to_wstring(playerID) + L"番のプレイヤーのVirtualPadの接続を開始します。このメッセージを閉じた後にお手元のVirtualPadへIPアドレスの入力・接続をお願いします。\nアプリはフォルダ内にある.apkファイルをお手元のAndroidにインストールするか、同フォルダに入っていますQRコードからインストールしてください。";
		const wchar_t*	_message	= _wstr.c_str();
		YUSTK::MessageBox_OK(_message, L"VirtualPad接続準備");

		// 成功なら更新
		if (vpManager_->TCP_Connection(playerID) == TCP_CONNECT_OK) {
			inputSystemList_[playerID] = InputSystem::VIRTUAL_PAD;
			return true;
		}

		inputSystemList_[playerID] = InputSystem::COM;
		return false;
	}

	static UseKeyChecker*							instance_;
	std::vector<InputSystem>						inputSystemList_;
	std::vector<std::unique_ptr<UseKeyFuncSets>>	inputList_;
	std::unique_ptr<VPManager>						vpManager_;
	std::wstring									hostName_;
	std::wstring									ipAddress_;
};