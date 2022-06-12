/**
 * @file WireList.h
 * @brief ボールのリストクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <vector>
#include "ObjWire.h"

//前方宣言
class BallsInstructor;
class PlayersInstructor;

class WireList {
public:
	WireList();
	virtual ~WireList();

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void AddWorld(btDynamicsWorld* physics_world_);
	void RemoveWorld(btDynamicsWorld* physics_world_);

	void SetInstructors(BallsInstructor* blInstructor, PlayersInstructor* plInstuructor);

	/**
	* @brief ワイヤーリストを返す
	* @return ワイヤーリスト
	*/
	std::vector<ObjWire*> GetList() const { return list_; }

private:
	std::vector<ObjWire*> list_;
};