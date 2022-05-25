#include "ObjectBase.h"
#include "_Classes/_CellList/_Cell/Cell.h"

ObjectBase::ObjectBase() {
	SetMember(NONE_OBJ_ID, NONE_COLLI_TYPE, Vector3::Zero, 0.0f);
}

ObjectBase::ObjectBase(OBJ_TYPE kind, COLLI_TYPE collision, Vector3 pos, float r) {
	SetMember(kind, collision, pos, r);
}

ObjectBase::~ObjectBase() {
	if (collision_ != nullptr) {
		delete collision_;
		collision_ = nullptr;
	}
	if (cp_ != nullptr) {
		cp_->Remove();
		delete cp_;
		cp_ = nullptr;
	}
}

/**
* @brief �����o�ϐ��̏�����
* @param kind ���̂̎��
* @param collision�@�����蔻��̌`��
* @param pos ���W
* @param r ���a
*/
void ObjectBase::SetMember(OBJ_TYPE kind, COLLI_TYPE collision, Vector3 pos, float r) {
	this->obj_type_ = kind;
	this->pos_.x = pos.x;
	this->pos_.y = pos.y;
	if (this->cp_ == nullptr)
		this->cp_ = new Cell(this);  // ���������Ԃ����蓖�Ă邽��

	rotate_ = Vector2::Zero;
	forward_ = Vector2::Zero;
	collision_ = new bdCollision(collision);
}

/**
* @brief �Փ˂������̂�Ԃ�
* @param m ����
* @return �Փ˂�������(�Ȃ����nullptr)
*/
ObjectBase* ObjectBase::GetCollision(ObjectBase* m) {
	OBJ_TYPE type = m->myObjectType();
	if (this->obj_type_ == type)
		return nullptr;

	if (this->obj_type_ != OBJ_TYPE::WIRE) {
		//�������v���C���[

		if (m->myObjectType() != OBJ_TYPE::WIRE) {
			//���̓��m�̏Փ˔���(�{�[���ƃv���C���[)
			if (this->collision_->GetBoundingSph().Intersects(m->collision_->GetBoundingSph())) {
				return m;
			}
		}
		else {
			//���̂ƒ����̂̏Փ˔���(�{�[��or�v���C���[�ƃ��C���[)
			if (this->collision_->GetBoundingSph().Intersects(m->collision_->GetBoundingBox())) {
				return m;
			}
		}
	}
	else {
		//���������C���[
		//���肪���̂Ɗm�肵�Ă���
		if (this->collision_->GetBoundingBox().Intersects(m->collision_->GetBoundingSph())) {
			return m;
		}
	}

	return nullptr;
}

/**
* @brief ������Ԃ̍X�V
*/
void ObjectBase::UpdateToMorton() {
	if (cp_ != nullptr)
		cp_->UpdateToMorton();
}

/**
* @brief �Փ˂������̂�Ԃ�
* @return �Փ˂�������
*/
ObjectBase* ObjectBase::GetHitObject() {
	return cp_->GetCollision();  // ����A�����x���A������3�����𒲂ׂ�(�l���ؒT��)
}