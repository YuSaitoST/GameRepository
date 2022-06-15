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

class ObjBall final : public ObjectBase {
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

	void WasCaught(const int ownerID, DirectX::XMFLOAT2* handPos);
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
	void SetPhysicsPosition(Vector3 position) {
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

	const float POS_Z_AT_GOAL = 1000.0f;

	XMFLOAT2*	ownerHandPos_;	//! ������̎茳�̍��W
	BallState*	state_;			//! �{�[���̏��
	COLOR_TYPE	colorType_;		//! ���݂̐F�̏��

	float	pos_z_;				//! Z���W
	int		id_owner_;			//! �������ID
	bool	isInPlayerHands_;	//! �v���C���[�̎茳�ɂ��邩
	bool	isBreak_;			//! �j�󂳂ꂽ��
};