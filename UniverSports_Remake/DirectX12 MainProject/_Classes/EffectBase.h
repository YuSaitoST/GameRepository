/**
 * @file EffectBase.h
 * @brief �G�t�F�N�g�̊��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Base/DX12Effekseer.h"
#include "_Classes/_UI/_CountTimer/CountTimer.h"

using namespace DirectX;

class EffectBase {
public:
	EffectBase() : effect_(EFFECT()) { SetMember(0.0f); }
	EffectBase(const float time) { SetMember(time); }
	virtual ~EffectBase() {};

	inline void SetMember(const float time) {
		timer_ = new CountTimer(time);
	}

	virtual void Initialize(std::string eff_name) { name_ = eff_name; }
	virtual void LoadAsset(std::wstring file_name) { effect_ = DX12Effect.Create(file_name.c_str(), name_); }

	/**
	* @brief �^�C�}�[�����Z�b�g����
	*/
	virtual void ResetTime() { timer_->Reset(); }

	/**
	* @brief ���W�𒲐�����
	* @position ���W
	*/
	virtual void Set_Position(SimpleMath::Vector3 position) { DX12Effect.SetPosition(name_, position); }

	/**
	* @brief ��]������
	* @param rotate ��]
	*/
	virtual void Set_Rotate(SimpleMath::Vector3 rotate) { DX12Effect.SetRotation(name_, rotate); }

	/**
	* @brief �T�C�Y����
	* @param scale �T�C�Y
	*/
	virtual void Set_Scale(SimpleMath::Vector3 scale) { DX12Effect.SetScale(name_, scale); }

	/**
	* @brief �Đ�
	*/
	virtual void Play() { DX12Effect.Play(name_); }

	/**
	* @brief �P���Đ�
	*/
	virtual void PlayOneShot() { DX12Effect.PlayOneShot(name_); }

	/**
	* @brief ��~
	*/
	virtual void Pause() { DX12Effect.Pause(name_); }

	/**
	* @brief �ړ�
	* @param movement �ړ���
	*/
	virtual void Move(SimpleMath::Vector3 movement) { DX12Effect.MoveEffect(name_, movement); }

	/**
	* @brief �^�C�}�[�̌v��
	* @param deltaTime �t���[�����Ƃ̌o�ߎ���
	*/
	virtual void TimerCount(const float deltaTime) { timer_->Update(deltaTime); }

	/**
	* @brief �^�C�}�[�̏I����Ԃ�Ԃ�
	* @return �^�C�}�[�̏I�����
	*/
	virtual bool isOver() { return timer_->TimeOut(); }

protected:
	//! �G�t�F�N�g
	EFFECT		effect_;
	
	//! �Đ����ԃ^�C�}�[
	CountTimer*	timer_;
	
	//! �G�t�F�N�g��
	std::string name_;
};