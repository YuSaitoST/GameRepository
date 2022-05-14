/**
 * @file UseKeyCheck.h
 * @brief �Q�[���ŗp������͂��Ǘ�����N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "KeyBoadChecker.h"
#include "GamePadChecker.h"

//�}�N��
#define Press UseKeyCheck::GetInstance()

class UseKeyCheck {
public:
	static UseKeyCheck& GetInstance() { return inctance_; }

	void Accepts();

	bool AnyKey();
	bool TabKey();
	bool UpKey(const int index);
	bool DownKey(const int index);
	bool LeftKey(const int index);
	bool RightKey(const int index);
	bool DecisionKey(const int index);
	bool CancelKey(const int index);
	bool MiniGameFinedKey(const int index);

	bool ThrasherKey(const int index);
	bool ShotKey(const int index);
	Vector2 MoveDirection(const int index);

private:
	UseKeyCheck() {}
	virtual ~UseKeyCheck() {}

	inline bool KeyEventA(const int index);
	inline bool KeyEventB(const int index);

	static UseKeyCheck inctance_;
	KeyBoadChecker key_;
	GamePadChecker pad_;
};