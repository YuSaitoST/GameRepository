/**
 * @file EffThrasher.h
 * @brief �X���X�^�[�G�t�F�N�g�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <algorithm>
#include "_Classes/_InputManager/UseKeyChecker.h"
#include "_Classes/_ConstStrages/ConstStorages.h"
#include "_Classes/EffectBase.h"

class EffThrasher final : public EffectBase {
public:
	EffThrasher();
	virtual ~EffThrasher() {};
	
	void Update(const float deltaTime, float rotate_x, Vector3 position, Vector3 direction, float proportion);

	//! �����g�p
	bool usedThrasher_;

private:
	//! �X���X�^�[�̉����̃y�[�X
	std::unique_ptr<CountTimer> timer_roop_;
};