/**
 * @file TeamID.h
 * @brief チームIDクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "DontDestroyOnLoad.h"

class TeamID {
public:
	TeamID() : id_(-1) {}
	virtual ~TeamID() {}

	/**
	* @brief チームIDをセットする
	* @param teamID セットするチームID
	*/
	void Set(const int teamID) { assert((id_ == -1) + "TeamID::Set() : 複数回目の呼び出しです"); id_ = teamID; }

	/**
	* @brief チームIDを返す
	* @return チームID
	*/
	int Get() const { return id_; }

	/**
	* @brief 個人IDからチームIDを求めるて返す
	* @param playerID 個人ID
	* @return チームID
	*/
	int Get(const int playerID) { return DontDestroy->TeamID[playerID]; }

private:
	//! チームID
	int id_;
};