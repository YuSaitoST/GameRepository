#include "ObjectBase.h"
#include "_Classes/_CellList/_Cell/Cell.h"

ObjectBase::ObjectBase() {
	SetMember(NONE, Vector3::Zero, 0.0f);
}

ObjectBase::ObjectBase(OBJ_ID kind, Vector3 pos, float r) {
	SetMember(kind, pos, r);
}

ObjectBase::~ObjectBase() {
	if (cp_ != nullptr) {
		cp_->Remove();
		delete cp_;
	}
}

void ObjectBase::SetMember(OBJ_ID kind, Vector3 pos, float r) {
	this->obj_type_ = kind;
	this->pos_.x = pos.x;
	this->pos_.y = pos.y;
	this->isHit_ = false;
	if (this->cp_ == nullptr)
		this->cp_ = new Cell(this);  // ���������Ԃ����蓖�Ă邽��

	collision_ = new bsCollider();
	physics_ = new btObject(pos);
}

ObjectBase* ObjectBase::IsCollision(ObjectBase* m) {
	if (collision_->GetBounding().Intersects(m->collision_->GetBounding()))
		return m;
	
	return nullptr;
}

// ���ǂ�Ƃ��ꂪ1�ԍŏ��ɌĂ΂��Collision()�ɂȂ�݂���
ObjectBase* ObjectBase::IsCollision() {
	ObjectBase* _cm = cp_->IsCollision();  // ���̒��ŁA����A�����x���A������3�����𒲂ׂ�
	return _cm;
}

void ObjectBase::Update() {
	// ���݂���Ȃ�A������Ԃ̍X�V������
	if (cp_ != nullptr)
		cp_->UpdateToMorton();

	// �ڐG����
	isHit_ = (IsCollision() != nullptr);
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