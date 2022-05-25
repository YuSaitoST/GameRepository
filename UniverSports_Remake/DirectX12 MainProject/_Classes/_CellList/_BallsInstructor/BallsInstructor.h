/**
 * @file BallsInstructor.h
 * @brief ボールの状態変化の指示クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

//前方宣言
class ObjBall;

class BallsInstructor {
public:
	BallsInstructor() {}
	virtual ~BallsInstructor() {}

	void SetList(const std::vector<ObjBall*>& balllist) { list_ = balllist; }

	void Cautch(const int playerID, const int ballID);
	void Shot(const int ballID, DirectX::SimpleMath::Vector2 forwrad);
	void BreakOfThrower(const int ballID);
	void BreakOfTheHitter(const int ballID);

private:
	//! ボールのリスト
	std::vector<ObjBall*> list_;
};