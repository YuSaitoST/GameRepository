#pragma once

enum CHARA_STATE {
	PLAYING,
	BEATEN,
	CHARASTATE_NONE
};

class ObjPlayer;

class CharaState {
public:
	CharaState() {}
	virtual ~CharaState() {}

	virtual void Initialize(int id, ObjPlayer* player) = 0;
	virtual void LoadAssets() = 0;
	virtual void Update(const float deltaTime) = 0;

	virtual float GetRotateX() = 0;
};

/*
	[やること]
	・試合中とやられた時で処理を切り替える
	・エフェクトは、それぞれのSTATE内で読み込むデータを変える

	<Playing>    <Beaten>
	スラスター : 爆破
	モデル     :  -
	collision  :  -
	基本動作   : 待機プログラムと爆破エフェクト再生のみ
	無敵       :  -
*/