/**
 * @file GameModes.h
 * @brief �Q�[�����[�h�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 /**
  * @enum GAMEMODE
  * ��������Ă���Q�[�����[�h
  */
enum GAMEMODE { DODGE_BALL_NOMAL, DODGE_BALL_2ON2, HAND_BALL, BILLIARDS, NONE_GAMEMODE };

class GameModes {
public:
	GameModes() : GameMode_(NONE_GAMEMODE) {}
	virtual ~GameModes() {}

	/**
	* @brief �I�������Q�[�����[�h��ݒ肷��
	* @param gameMode �I�������Q�[�����[�h
	*/
	inline void SelectMode(GAMEMODE gameMode) { GameMode_ = gameMode; }

	/**
	* @brief �V���O���X�̃Q�[�����[�h����Ԃ�
	* @return �V���O���X�̃Q�[�����[�h�Ȃ�true�@�قȂ�Ȃ�false
	*/
	inline bool isSINGLES_GAME() const { return !isDODGEBALL_2ON2(); }

	/**
	* @brief �S�[����p����Q�[�����[�h����Ԃ�
	* @return �S�[����p����Q�[�����[�h�Ȃ�true�@�قȂ�Ȃ�false
	*/
	inline bool isGAMES_WITH_GOALS() const { return isHANDBALL() || isBILLIARDS(); }

	/**
	* @brief �h�b�W�{�[���n�̃��[�h����Ԃ�
	* @return �h�b�W�{�[���n�̃��[�h�Ȃ�true�@�قȂ�Ȃ�false
	*/
	inline bool isDODGEBALL() const { return isDODGEBALL_NOMAL() || isDODGEBALL_2ON2();	}

	/**
	* @brief �h�b�W�{�[�����[�h����Ԃ�
	* @return �h�b�W�{�[�����[�h�Ȃ�true�@�قȂ�Ȃ�false
	*/
	inline bool isDODGEBALL_NOMAL() const { return GameMode_ == DODGE_BALL_NOMAL;}

	/**
	* @brief �h�b�W�{�[��2on2���[�h����Ԃ�
	* @return �h�b�W�{�[��2on2���[�h�Ȃ�true�@�قȂ�Ȃ�false
	*/
	inline bool isDODGEBALL_2ON2() const { return GameMode_ == DODGE_BALL_2ON2;	}

	/**
	* @brief �n���h�{�[�����[�h����Ԃ�
	* @return �n���h�{�[�����[�h�Ȃ�true�@�قȂ�Ȃ�false
	*/
	inline bool isHANDBALL() const { return GameMode_ == HAND_BALL; }

	/**
	* @brief �r�����[�h���[�h����Ԃ�
	* @return �r�����[�h���[�h�Ȃ�true�@�قȂ�Ȃ�false
	*/
	inline bool isBILLIARDS() const { return GameMode_ == BILLIARDS; }

	/**
	* @brief ���[�h�̌����Ԃ�Ԃ�
	* @return ���肳��Ă��Ȃ����true
	*/
	inline bool isNotDecision() const { return GameMode_ == NONE_GAMEMODE; }

	/**
	* @brief ���v���C���Ă��郂�[�h��Ԃ�
	* @return �i�s���̃��[�h
	*/
	inline GAMEMODE SelectionMode() const { return GameMode_; }

private:
	//! �Q�[�����[�h��ۑ�����ϐ�
	GAMEMODE GameMode_;
};