#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "bdCollision.h"
#include "btObject.h"

using namespace DirectX::SimpleMath;
class Cell;

enum OBJ_TYPE { PLAYER, BALL, WIRE, NONE_OBJ_ID };

class ObjectBase {
public:
	ObjectBase();
	ObjectBase(OBJ_TYPE kind, COLLI_TYPE collision, Vector3 pos, float r);
	virtual ~ObjectBase();

	virtual void Initialize(const int id) = 0;
	virtual void LoadAssets(std::wstring file_name) = 0;
	virtual void LoadAssets(DX9::MODEL& model) = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Render(DX9::MODEL& model) = 0;
	virtual void UIRender() = 0;

	virtual void HitAction(ObjectBase* hitObject) = 0;

	virtual ObjectBase* GetCollision(ObjectBase* m);  // �Փ˔���(Bounding��p��������)

	static D3DMATERIAL9 GetNomMaterial() {
		D3DMATERIAL9 _mate{};
		_mate.Diffuse = DX9::Colors::Value(0.3f, 0.3f, 0.3f, 1.0f);
		_mate.Ambient = DX9::Colors::Value(0.7f, 0.7f, 0.7f, 1.0f);
		return _mate;
	}

	ObjectBase* GetHitObject();

	OBJ_TYPE		myObjectType() { return obj_type_; }
	btRigidBody*	myRigidbody() { return physics_->Get_RigidBody(); }
	Vector2&		myPosition() { return pos_; }
	Vector2			myRotate() { return rotate_; };
	Vector2&		myDirection() { return forward_; }
	float			myRadian() { return r_; }
	int				myObjectID() { return id_my_; };

protected:
	virtual void SetMember(OBJ_TYPE kind, COLLI_TYPE collision, Vector3 pos, float r);
	
	void UpdateToMorton();

	OBJ_TYPE obj_type_;		// �I�u�W�F�N�g�̎��
	bdCollision* collision_;// �����蔻��
	btObject* physics_;		// �������Z
	Cell* cp_;				// �������
	Vector2 pos_;			// ���W
	Vector2 rotate_;		// ��]
	Vector2 forward_;       // ���ʕ���
	float r_;               // ���a
	int id_my_;			    // ������ID
};