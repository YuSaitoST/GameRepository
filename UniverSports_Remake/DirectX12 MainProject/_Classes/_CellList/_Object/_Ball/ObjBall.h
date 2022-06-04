/**
 * @file ObjBall.h
 * @brief �{�[���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/ObjectBase.h"
#include "_State/BallState.h"
#include "_State/_Standby/StStandby.h"
#include "_State/_Float/StFloat.h"
#include "_State/_Cautch/StCautch.h"
#include "_State/_Shot/StShot.h"
#include "_State/_Goal/StGoal.h"

class ObjBall final : public ObjectBase {
private:
	//! �v���C���[�̃f�B�t���[�Y�F
	const D3DCOLORVALUE P_DIFFUSE[5] = {
		D3DCOLORVALUE(0.0f,0.65f,0.0f,1.0f),	// ��(PL.1)
		D3DCOLORVALUE(0.65f,0.0f,0.65f,1.0f),	// ��(PL.2)
		D3DCOLORVALUE(0.65f,0.0f,0.0f,1.0f),	// ��(PL.3)
		D3DCOLORVALUE(0.0f,0.0f,0.65f,1.0f),	// ��(PL.4)
		D3DCOLORVALUE(0.0f,0.0f,0.0f,0.0f)
	};
	//! �A���r�G���g�F
	const D3DCOLORVALUE P_AMBIENT = D3DCOLORVALUE(0.35f, 0.35f, 0.35f, 1.0f);

public:
	/**
	* @enum COLOR_TYPE
	* �{�[���̐F
	*/
	enum COLOR_TYPE { DEFAULT_COLOR, PLAYERS_COLOR, TEAM_COLOR };

public:
	ObjBall();
	ObjBall(Vector3 pos, float r);
	virtual ~ObjBall();

	virtual void Initialize(const int id);
	virtual void LoadAssets(std::wstring file_name) {}
	virtual void LoadAssets(DX9::MODEL& model);
	virtual void Update(const float deltaTime);
	virtual void Render() {}
	virtual void Render(DX9::MODEL& model);
	virtual void UIRender() {}

	virtual void HitAction(ObjectBase* hitObject) {}

	void WasCaught(const int ownerID);
	void WasThrown(Vector2 forward);
	void WasGoaled();
	void WasGuessed();
	void BallBreak();

	/**
	* @brief �F�̕ύX
	* @param colorType �F�̃^�C�v
	*/
	inline void SwitchColor(COLOR_TYPE colorType) { colorType_ = colorType; }

	void SwitchState(BallState* state);

	/**
	* @brief �͂������Ĕ�΂�����
	* @param power �������
	*/
	void Moving(Vector3 power) { physics_->Moving(power); }
	void Following(float pos_z);
	void AddPower(XMFLOAT3 forward, float speed);
	void AssignPosition() { pos_ = physics_->GetCenterOfMassPosition(); }

	/**
	* @brief ���W�Ɛ��ʃx�N�g����ݒ肷��
	* @param position ���W
	* @param forward ���ʃx�N�g��
	*/
	void AssignTransform(Vector3 position, Vector2 forward) {
		pos_ = Vector2(position.x, position.y);
		pos_z_ = position.z;
		forward_ = forward;
	}

	/**
	* @brief ���̃I�u�W�F�N�g�ɍ��W��ݒ肷��
	* @param position ���W
	*/
	void PhysicsControll(Vector3 position) {
		AssignTransform(position, Vector2::Zero);
		physics_->SetCenterOfMassTransform(Vector3(pos_.x, pos_.y, pos_z_), Vector3::Zero);
	}
	
	/**
	* @brief �������ID���Z�b�g����
	*/
	inline void SetOwnerID(int id_player) { id_owner_ = id_player; }
	
	/**
	* @brief �{�[����j�󂳂ꂽ��Ԃɂ���
	*/
	inline void SetBallBreak(bool flag) { isBreak_ = flag; }
	
	/**
	* @brief ������̎茳�̍��W��ۑ�����
	* @param handPos �茳�̍��W
	*/
	inline void SetOwnerHandPos(XMFLOAT2* handPos) { ownerHandPos_ = handPos; }

	/**
	* @brief ��ԃt���O��S�ă��Z�b�g����
	*/
	inline void FlagResets() { isInPlayerHands_ = isBreak_ = false; }
	
	/**
	* @brief �������ID��Ԃ�
	* @return �������ID
	*/
	inline int GetOwnerID() const { return id_owner_; }

	/**
	* @brieff Z���W��Ԃ�
	* @return Z���W
	*/
	inline float myPosZ() const { return pos_z_; }

	/**
	* @brief ������̎茳�ɂ��邩��Ԃ�
	* @return ������̎茳�ɂ����true
	*/
	inline bool IsInPlayerHands() const { return isInPlayerHands_; }

	/**
	* @brief �j�󂳂ꂽ����Ԃ�
	* @return �j�󂳂�Ă����true
	*/
	inline bool IsBreaked() const { return isBreak_; }

	/**
	* @brief ���݂̏�Ԃ�Ԃ�
	* @return ���݂̏��
	*/
	inline B_STATE NowState() const { return state_->GetMyState(); }

private:
	D3DMATERIAL9 ChangeMaterial(COLOR_TYPE colorType);

	//! ������̎茳�̍��W
	XMFLOAT2* ownerHandPos_;

	//! �{�[���̏��
	BallState* state_;

	//! �ҋ@���
	StStandby st_standby_;
	
	//! ���V���
	StFloat st_float_;
	
	//! �L���b�`����Ă�����
	StCautch st_cautch_;

	//! ������ꂽ���
	StShot st_shot_;

	//! �S�[���ɓ��������
	StGoal st_goal_;

	//! ���݂̐F�̏��
	COLOR_TYPE colorType_;

	//! Z���W
	float pos_z_;

	//! �������ID
	int id_owner_;

	//! �v���C���[�̎茳�ɂ��邩
	bool isInPlayerHands_;

	//! �j�󂳂ꂽ��
	bool isBreak_;
};