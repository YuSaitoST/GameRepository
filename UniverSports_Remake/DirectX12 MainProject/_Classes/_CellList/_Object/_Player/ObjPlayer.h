/**
 * @file ObjPlayer.h
 * @brief �v���C���[�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/ObjectBase.h"
#include "_Classes/_CellList/_Object/_Player/_MyLife/MyLife.h"
#include "_Classes/_CellList/_Object/_Ball/ObjBall.h"
#include "_Classes/_CellList/_TeamID/TeamID.h"
#include "_Strategy/CharaStrategy.h"
#include "_Strategy/_ManualChara/ManualChara.h"
#include "_Strategy/_ComputerChara/ComputerChara.h"
#include "_Barrier/Barrier.h"
#include "_EffDown/EffDown.h"

//�O���錾
class BallsInstructor;

class ObjPlayer final : public ObjectBase {
private:
	/**
	* @enum MOTION
	* �v���C���[���f���ɓo�^����Ă���A�j���[�V����
	*/
	enum MOTION {
		STAND,
		STAND_TO_CATCH,
		HAND,
		HAND_TO_READY,
		READY,
		IS_SHOT
	};

public:
	ObjPlayer();
	ObjPlayer(OPERATE_TYPE strategy, Vector3 pos, float r);
	virtual ~ObjPlayer();

	virtual void Initialize(const int id);
	virtual void LoadAssets(std::wstring file_name);
	virtual void LoadAssets(DX9::MODEL& model) {}
	virtual void Update(const float deltaTime);
	virtual void Render();
	virtual void Render(DX9::MODEL& model) {}
	virtual void UIRender();
	void AlphaRender();

	virtual void HitAction(ObjectBase* hitObject);

	void SetInstructor(BallsInstructor* instructor) { instructor_ = instructor; }

	void CreateModel(std::wstring fileName);

	/**
	* @brief ���f���̕ύX
	*/
	void ReDecision(const int plID, const std::wstring fileName) {
		CreateModel(fileName);
		pos_ = Vector2(GAME_CONST.S_POS[plID].x, GAME_CONST.S_POS[plID].y);
		rotate_ = Vector2(0.0f, GAME_CONST.Player_FacingRight);
		SetTransforms(pos_, rotate_);
	}

	/**
	* @brief ����^�C�v�̕ύX
	*/
	void ChangeStrategy() {
		strategy_ = new ComputerChara();
		strategy_->Initialize(id_my_, this);
	}

	/**
	* @brief �ړ�����
	*/
	void Moving(Vector3 power) { physics_->Moving(power); };

	void Shoting(const int ballID);
	void CautchedBall(const int ballID);

	/**
	* @brief ���̃I�u�W�F�N�g�̒��S���W���擾����
	*/
	void AssignPosition() { pos_ = physics_->GetCenterOfMassPosition(); }

	/**
	* @brief �c�@����Ԃ�
	* @return �c�@��
	*/
	int myLife() const { return life_->NowLifePoint(); }
	
	/**
	* @brief �{�[���̏�����Ԃ�Ԃ�
	* @return �{�[���̏������
	*/
	bool HasBall() const { return hasBall_; }
	Vector2 Get_HandPos();

	/**
	* @brief �������Ă���{�[����ID��Ԃ�
	* @return �������Ă���{�[����ID
	*/
	int MyBallID() const { return myBallID_; }

	/**
	* @brief �C���X�g���N�^�[��Ԃ�
	* @return �C���X�g���N�^�[
	*/
	BallsInstructor* GetInstructor() const { return instructor_; }

private:
	void Playing(const float deltaTime);
	void Beaten(const float deltaTime);

	void SetTransforms(XMFLOAT2 pos, XMFLOAT2 rotate);
	void AnimReset();
	void AnimSet(MOTION motion, float deltaTime);

	/**
	* @brief ����ɍ������A�j���[�V������Ԃ�
	* @return �A�j���[�V�����̔ԍ�
	*/
	MOTION AnimChange();

	const SimpleMath::Vector2 POS_HAND = { -2.75f, -3.0f };

	std::unique_ptr<MyLife>				life_;			//! �c�@
	std::unique_ptr<TeamID>				teamID_;		//! �`�[��ID
	std::unique_ptr<CountTimer>			ti_respone_;	//! ���X�|�[���^�C�}�[
	std::unique_ptr<EffDown>			eff_down_;		//! �_�E�����G�t�F�N�g
	std::unique_ptr<Barrier>			barrier_;		//! �o���A
	
	CharaStrategy*		strategy_;		//! �s��
	BallsInstructor*	instructor_;	//! �{�[���C���X�g���N�^�[

	DX9::SKINNEDMODEL	model_;			//! ���f��

	bool				hasBall_;		//! �{�[���̏������
	bool				isDown_;		//! ������
	int					myBallID_;		//! �������Ă���{�[����ID
};