#include "ObjectBase.h"
#include "_Classes/_CellList/_Cell/Cell.h"

ObjectBase::ObjectBase() {
	SetMember(NONE_OBJ_ID, NONE_COLLI_TYPE, Vector3::Zero, 0.0f);
}

ObjectBase::ObjectBase(OBJ_TYPE kind, COLLI_TYPE collision, Vector3 pos, float r) {
	SetMember(kind, collision, pos, r);
}

ObjectBase::~ObjectBase() {
	if (cp_ != nullptr) {
		cp_->Remove();
		delete cp_;
	}
}

void ObjectBase::SetMember(OBJ_TYPE kind, COLLI_TYPE collision, Vector3 pos, float r) {
	this->obj_type_ = kind;
	this->pos_.x = pos.x;
	this->pos_.y = pos.y;
	if (this->cp_ == nullptr)
		this->cp_ = new Cell(this);  // 所属する空間を割り当てるため

	rotate_ = Vector2::Zero;
	forward_ = Vector2::Zero;
	collision_ = new bdCollision(collision);
}

ObjectBase* ObjectBase::IsCollision(ObjectBase* m) {
	if (this->obj_type_ == m->myObjectType())
		return nullptr;

	const COLLI_TYPE type_1 = collision_->GetType();
	const COLLI_TYPE type_2 = m->collision_->GetType();

	BoundingSphere sphere_1;
	BoundingSphere sphere_2;
	BoundingOrientedBox box;

	// 自身のcollisionを用意
	if (type_1 == SPHRER)
		sphere_1 = collision_->GetBoundingSph();
	else if (type_1 == ORIENTEDBOX)
		box = collision_->GetBoundingBox();

	// 相手のcollisionを用意
	if (type_2 == SPHRER)
		sphere_2 = m->collision_->GetBoundingSph();
	else if (type_2 == ORIENTEDBOX)
		box = m->collision_->GetBoundingBox();

	// 衝突判定
	if (type_1 == SPHRER && type_1 == type_2) {
		// キャラtoキャラ or キャラtoボール or ボールtoキャラ or ボールtoボール
		if (sphere_1.Intersects(sphere_2))
			return m;
	}
	else if ((type_1 == SPHRER && type_2 == ORIENTEDBOX) || (type_1 == ORIENTEDBOX && type_2 == SPHRER))
		// ワイヤーとキャラorボール
		if (sphere_1.Intersects(box))
			return m;

	return nullptr;
}

void ObjectBase::UpdateToMorton() {
	// 存在するなら、所属空間の更新をする
	if (cp_ != nullptr)
		cp_->UpdateToMorton();
}

ObjectBase* ObjectBase::IsHitObject() {
	return cp_->IsCollision();  // 上方、同レベル、下方の3方向を調べる(四分木探索)
}

void ObjectBase::ClampLoop(Vector2& pos) {
	if (pos.x < -GAME_CONST.FieldSide_X)
		pos.x = GAME_CONST.FieldSide_X;
	else if (GAME_CONST.FieldSide_X < pos.x)
		pos.x = -GAME_CONST.FieldSide_X;

	if (pos.y < -GAME_CONST.FieldSide_Y)
		pos.y = GAME_CONST.FieldSide_Y;
	else if (GAME_CONST.FieldSide_Y < pos.y)
		pos.y = -GAME_CONST.FieldSide_Y;
}

bool ObjectBase::IsFieldOut(Vector2& pos, float size) {
	const bool _isOut_x = pos.x + size < -GAME_CONST.FieldSide_X || GAME_CONST.FieldSide_X < pos.x - size;
	const bool _isOut_y = pos.y + size < -GAME_CONST.FieldSide_Y || GAME_CONST.FieldSide_Y < pos.y - size;

	return _isOut_x || _isOut_y;
}