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

	/**
	* @brief ���f������
	* @param fileName �t�@�C����
	*/
	void CreateModel(std::wstring fileName) {
		model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, fileName.c_str());
		model_->SetScale(0.018f);
		model_->SetMaterial(GetNomMaterial());
	}

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

	void AsjustmentForward();

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

private:
	void Playing(const float deltaTime);
	void Beaten(const float deltaTime);

	void SetTransforms(const Vector2 pos, const Vector2 rotate);
	void AnimReset();
	void AnimSet(MOTION motion, float deltaTime);

	/**
	* @brief ����ɍ������A�j���[�V������Ԃ�
	* @return �A�j���[�V�����̔ԍ�
	*/
	MOTION AnimChange();

	const SimpleMath::Vector2 POS_HAND = { -2.75f, -3.0f };

	//! �c�@
	MyLife*				life_;
	
	//! �`�[��ID
	TeamID*				teamID_;
	
	//! ���X�|�[���^�C�}�[
	CountTimer*			ti_respone_;
	
	//! �_�E�����G�t�F�N�g
	EffDown*			eff_down_;
	
	//! �s��
	CharaStrategy*		strategy_;
	
	//" �o���A
	Barrier*			barrier_;
	
	//! ���f��
	DX9::SKINNEDMODEL	model_;
	
	//! �{�[���̏������
	bool				hasBall_;
	
	//! ������
	bool				isDown_;
	
	//! �������Ă���{�[����ID
	int					myBallID_;
};