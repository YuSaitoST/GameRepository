#include "ObjBall.h"

ObjBall::ObjBall() {
	cp_ = nullptr;
	SetMember(NONE_OBJ_ID, Vector3::Zero, 0.0f);

	rotate_ = Vector2::Zero;
	pos_z_ = 0.0f;
}

ObjBall::ObjBall(Vector3 pos, float r) {
	cp_ = nullptr;
	SetMember(BALL, pos, r);

	rotate_ = Vector2(0.0f, GAME_CONST.Player_FacingRight);
	pos_z_ = 0.0f;
}

ObjBall::~ObjBall() {

}

void ObjBall::Initialize(const int id) {
	id_my_ = id;
}

/*
	＊注意！
	以下のコードは内容があまり決まっていない
	調整はじっくりと...
*/

void ObjBall::LoadAssets(DX9::MODEL model) {

}

void ObjBall::Update(const float deltaTime) {

}

void ObjBall::Render() {

}

void ObjBall::SetTransforms() {

}