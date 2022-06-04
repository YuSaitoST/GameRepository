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
#include "_Classes/_SoundPlayer/SoundPlayer.h"
#include "_Strategy/CharaStrategy.h"
#include "_Strategy/_ManualChara/ManualChara.h"
#include "_Strategy/_ComputerChara/ComputerChara.h"
#include "_Barrier/Barrier.h"
#include "_EffDown/EffDown.h"

//�O���錾
class BallsInstructor;
class PlayersInstructor;

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

	void SetInstructor(BallsInstructor* blInstructor, PlayersInstructor* plInstructor) { ballsInstructor_ = blInstructor; playersInstructor_ = plInstructor; }

	void CreateModel(std::wstring fileName);

	/**
	* @brief ���f���̕ύX
	*/
	void ReDecision(const int plID, const std::wstring fileName) {
		CreateModel(fileName);
		pos_ = XMFLOAT2(GAME_CONST.S_POS[plID].x, GAME_CONST.S_POS[plID].y);
		rotate_ = XMFLOAT2(0.0f, GAME_CONST.Player_FacingRight);
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

	///**
	//* @brief �茳�̍��W��Ԃ�
	//* @return �茳�̍��W�̃A�h���X
	//*/
	//XMFLOAT2* Get_HandPos() { return &handPos_; }

	/**
	* @brief �������Ă���{�[����ID��Ԃ�
	* @return �������Ă���{�[����ID
	*/
	int MyBallID() const { return myBallID_; }

	/**
	* @brief �{�[���C���X�g���N�^�[��Ԃ�
	* @return �{�[���C���X�g���N�^�[
	*/
	BallsInstructor* GetBallsInstructor() const { return ballsInstructor_; }

	/**
	* @brief �v���C���[�C���X�g���N�^�[��Ԃ�
	* @return �v���C���[�C���X�g���N�^�[
	*/
	PlayersInstructor* GetPlayersInstructor() const { return playersInstructor_; }

	/**
	* @brief �^�[�Q�b�g�v���C���[��ς���
	* @return �^�[�Q�b�g�v���C���[
	*/
	ObjectBase* GetTargetPlayer() const { return targetPlayer_; }

private:
	void Playing(const float deltaTime);
	void Beaten(const float deltaTime);

	void CalculationHandPos();
	void SetTransforms(XMFLOAT2 pos, XMFLOAT2 rotate);
	void AnimReset();
	void AnimSet(MOTION motion, float deltaTime);
	void SertchTarget();

	/**
	* @brief ����ɍ������A�j���[�V������Ԃ�
	* @return �A�j���[�V�����̔ԍ�
	*/
	MOTION AnimChange();

	const SimpleMath::Vector2 POS_HAND = { -2.75f, -3.0f };

	std::unique_ptr<MyLife>			life_;			//! �c�@
	std::unique_ptr<CountTimer>		ti_respone_;	//! ���X�|�[���^�C�}�[
	std::unique_ptr<EffDown>		eff_down_;		//! �_�E�����G�t�F�N�g
	std::unique_ptr<Barrier>		barrier_;		//! �o���A
	std::unique_ptr<SoundPlayer>	se_shot_;		//! �V���b�g��SE
	std::unique_ptr<SoundPlayer>	se_defeat_;		//! ���j��SE
	
	CharaStrategy*		strategy_;			//! �s��
	ObjectBase*			targetPlayer_;			//! �^�[�Q�b�g�̃I�u�W�F�N�g
	BallsInstructor*	ballsInstructor_;	//! �{�[���C���X�g���N�^�[
	PlayersInstructor*	playersInstructor_;	//! �v���C���[�C���X�g���N�^�[

	XMFLOAT2			handPos_;			//! �茳�̍��W

	DX9::SKINNEDMODEL	model_;				//! ���f��

	bool				hasBall_;			//! �{�[���̏������
	bool				isDown_;			//! ������
	int					myBallID_;			//! �������Ă���{�[����ID
};