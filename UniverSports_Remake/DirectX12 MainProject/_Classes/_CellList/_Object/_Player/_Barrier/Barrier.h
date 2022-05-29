/**
 * @file Barrier.h
 * @brief �o���A�N���X
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
#include "_Classes/_UI/_CountTimer/CountTimer.h"

class Barrier {
public:
	Barrier();
	virtual ~Barrier() {}

	void LoadAsset(float radius);
	void Update(const float deltaTime);
	void Render();

	/**
	* @brief ���W�ݒ�
	* @param position ���W
	*/
	void SetPosition(DirectX::XMFLOAT3 position) { mod_->SetPosition(position); };

	/**
	* @brief �o���A��\��������
	*/
	inline void DisprayOn() { isInvincible_ = true; }

	/**
	* @brief �\����Ԃ�Ԃ�
	* @return �\�����
	*/
	inline bool IsDisplayed() const { return isInvincible_; }

private:
	void SetMaterial();

	//! �\�����Ԃ̃^�C�}�[
	std::unique_ptr<CountTimer> timer_;

	//! �o���A���f��
	DX9::MODEL mod_;

	//! �\�����
	bool isInvincible_;
};