#pragma once

class ObjBall;

class BallState {
public:
	BallState() {}
	virtual ~BallState() {}

	virtual void Initialize() = 0;
	virtual void Update(const float deltaTime, ObjBall* ball) = 0;
};

/*
	[状態の種類]

	<共通項目>

	<相違項目>
	・浮遊 : ランダムな{座標,方向}の確定、
			 決めた位置をball->pos_に代入(ObjBall.Renderでセットされる)
	・捕獲 : 
	・投球 : 
*/