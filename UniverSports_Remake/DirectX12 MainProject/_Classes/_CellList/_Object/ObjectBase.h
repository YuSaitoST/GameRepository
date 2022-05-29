/**
 * @file ObjectBase.h
 * @brief ��Ԃɏ������镨�̂̊��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "bdCollision.h"
#include "btObject.h"

using namespace DirectX::SimpleMath;

//�O���錾
class Cell;

/**
* @enum OBJ_TYEP
* ���̂̎��
*/
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

	virtual ObjectBase* GetCollision(ObjectBase* m);

	ObjectBase* GetHitObject();

	/**
	* @brief �ʏ�̃}�e���A����Ԃ�
	* @return �ʏ�̃}�e���A��
	*/
	D3DMATERIAL9 GetNomMaterial() {
		D3DMATERIAL9 _mate{};
		_mate.Diffuse = DX9::Colors::Value(0.3f, 0.3f, 0.3f, 1.0f);
		_mate.Ambient = DX9::Colors::Value(0.7f, 0.7f, 0.7f, 1.0f);
		return _mate;
	}

	/**
	* @brief ���x�����Z�b�g����
	*/
	void ResetVelocity() { physics_->ResetVelocity(); }

	/**
	* @brief �����̕��̂̎�ނ�Ԃ�
	* @return ���̂̎��
	*/
	OBJ_TYPE myObjectType() { return obj_type_; }

	/**
	* @brief ���W�b�h�{�f�B��Ԃ�
	* @return ���W�b�h�{�f�B
	*/
	btRigidBody* myRigidbody() { return physics_->Get_RigidBody(); }

	/**
	* @brief ���W��Ԃ�
	* @return ���W
	*/
	Vector2& myPosition() { return pos_; }

	/**
	* @brief ��]��Ԃ�
	* @return ��]
	*/
	Vector2 myRotate() { return rotate_; };

	/**
	* @brief ���ʃx�N�g����Ԃ�
	* @return ���ʃx�N�g��
	*/
	Vector2& myDirection() { return forward_; }

	/**
	* @brief ���a��Ԃ�
	* @return ���a
	*/
	float myRadian() { return r_; }

	/**
	* @brief ������ID��Ԃ�
	* @return ������ID
	*/
	int	myObjectID() { return id_my_; };

protected:
	virtual void SetMember(OBJ_TYPE kind, COLLI_TYPE collision, Vector3 pos, float r);
	virtual void SetTransform(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 rotate);
	virtual void UpdateToMorton();

	std::unique_ptr<bdCollision> collision_;//! �����蔻��
	std::unique_ptr<btObject> physics_;		//! �������Z
	Cell* cp_;				//! �������
	OBJ_TYPE obj_type_;		//! �I�u�W�F�N�g�̎��
	Vector2 pos_;			//! ���W
	Vector2 rotate_;		//! ��]
	Vector2 forward_;       //! ���ʕ���
	float r_;               //! ���a
	int id_my_;			    //! ������ID
};