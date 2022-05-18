/**
 * @file TeamID.h
 * @brief �`�[��ID�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "DontDestroyOnLoad.h"

class TeamID {
public:
	TeamID() : id_(-1) {}
	virtual ~TeamID() {}

	/**
	* @brief �`�[��ID���Z�b�g����
	* @param teamID �Z�b�g����`�[��ID
	*/
	void Set(const int teamID) { assert((id_ == -1) + "TeamID::Set() : ������ڂ̌Ăяo���ł�"); id_ = teamID; }

	/**
	* @brief �`�[��ID��Ԃ�
	* @return �`�[��ID
	*/
	int Get() const { return id_; }

	/**
	* @brief �lID����`�[��ID�����߂�ĕԂ�
	* @param playerID �lID
	* @return �`�[��ID
	*/
	int Get(const int playerID) { return DontDestroy->TeamID[playerID]; }

private:
	//! �`�[��ID
	int id_;
};