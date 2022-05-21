/**
 * @file Gauge.h
 * @brief �X���X�^�[�̃Q�[�W�N���X
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
#include "_Classes/_MainCamera/MainCamera.h"

class Gauge {
public:
	Gauge();
	virtual ~Gauge() = default;

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, bool usedThrasher);
	void Render();

	/**
	* @brief ���W�ݒ�
	* @param position ���W
	*/
	void SetPosition(DirectX::XMFLOAT3 position) { position_ = position; };

	/**
	* @brief ���݂̒l��Ԃ�
	* @return ���݂̒l
	*/
	float GetProportion() const { return proportion_; };

private:
	/**
	* @ brief �Q�[�W�g�p
	* @ param deltaTime �t���[�����Ƃ̌o�ߎ���
	*/
	void IsDecrease(float& num, float speed, float min) { num = std::max(min, num - speed); }

	/**
	* @ brief �Q�[�W��
	* @ param deltaTime �t���[�����Ƃ̌o�ߎ���
	*/
	void IsRecovery(float& num, float speed, float max) { num = std::min(num + speed, max); }

	const int	RECT_Y		= 15;
	const float	MAX_GAUGE	= 71;
	const float GtoO		= 0.5f;
	const float OtoR		= 0.2f;
	const DirectX::XMFLOAT3 DISPLAY_POSITION = DirectX::XMFLOAT3(-35.0f, -60.0f, 0.0f);

	/**
	* @enum GAUGECOLOR
	* �Q�[�W�̒i�K�F
	*/
	enum GAUGECOLOR {
		GREEN, ORANGE, RED
	} color_;

	//! �Q�[�W�摜(����)
	DX9::SPRITE sp_gauge_L_[3];

	//! �Q�[�W�摜(�E��)
	DX9::SPRITE sp_gauge_R_[3];
	
	//! �Q�[�W�摜(�t���[��)
	DX9::SPRITE sp_flame_;

	//! ���W
	DirectX::SimpleMath::Vector3 position_;

	//! �g�p���̑��x
	float movement_decrease_;
	
	//! �񕜎��̑��x
	float movement_recovery_;

	//! ���݂̃Q�[�W�̒l(0.0f�`1.0f)
	float proportion_;

	//! �Q�[�W�̃T�C�Y�����Ƃ����Q�[�W�̒l
	float gauge_;

	//! �Q�[�W�̕\����
	float gauge_rect_x_;
};