#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class HitInstructor {
public:
	HitInstructor() {}
	virtual ~HitInstructor() {}

	static void BallCautch(const int playerID, const int ballID);
	static void BallShot(const int ballID, DirectX::SimpleMath::Vector2 forward);
	static void BallBreak(const int ballID);
};

/*
	[目的]
	〇以下の状況になった際に相手側に通知する
		・Playerが「浮きBall」をキャッチした時
		・Playerが「投げBall」にぶつかった時
		・PlayerがWireからボールを確保する時
		・BallがWireに入った時
	〇BallとWireを受け身にする
		-> 空間分割による、よけいな判定を減らす

	[使用イメージ]
	・主にPlayerが何かにぶつかった際に関数を呼び出す
		HitInstructor::BallCautch();

	[処理内容]
	(優先度高)
	・Playerが「浮きBall」をキャッチした時
		-> Ball) 取られた判定にする
	・Playerが「投げBall」にぶつかった時
		-> Ball) isBreak_をtrueにする
	(優先度低)
	・PlayerがWireからボールを確保する時
	・WireにBallが入った時(ループ回数減らせる(Wireで呼ぶと*4回、Ballで呼ぶと最低*5回))
*/