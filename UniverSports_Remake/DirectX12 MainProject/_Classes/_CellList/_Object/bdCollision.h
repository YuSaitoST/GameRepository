/**
 * @file bdCollision.h
 * @brief �����蔻��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"

using namespace DirectX;

/**
* enum COLLI_TYPE
* �����蔻��̌`��
*/
enum COLLI_TYPE{ SPHRER, ORIENTEDBOX, NONE_COLLI_TYPE };

class bdCollision {
public:
	bdCollision(COLLI_TYPE collision) { type_ = collision; }
	virtual ~bdCollision() {}


	/**
	* @brief ���W��ݒ肷��
	* @param pos ���W
	*/
	void SetPosition(SimpleMath::Vector3 pos) { (type_ == SPHRER) ? sph_.Center = pos : (type_ == ORIENTEDBOX) ? box_.Center = pos : XMFLOAT3(0.0f, 0.0f, 0.0f); }

	/**
	* @brief �����蔻��̓o�^(������)
	* @param bound ���̂̃R���W����
	*/
	void SetColli(BoundingOrientedBox bound) { box_ = bound; }

	/**
	* @brief �����蔻��̓o�^(����)
	* @param bound ���̂̃R���W����
	*/
	void SetColli(BoundingSphere bound) { sph_ = bound; }

	/**
	* @brief �T�C�Y�␳
	* @param scale �T�C�Y
	*/
	void SetColliScale(float scale) { sph_.Radius *= scale; }


	/**
	* @brief �R���W������Ԃ�(������)
	* @return �R���W����
	*/
	BoundingOrientedBox GetBoundingBox() const { return box_; }

	/**
	* @brief �R���W������Ԃ�(����)
	* @return �R���W����
	*/
	BoundingSphere GetBoundingSph() const { return sph_; }
	
private:
	//! �����蔻��̌`��
	COLLI_TYPE type_;

	//! ���̂̃R���W����
	BoundingSphere sph_;

	//! �����̂̃R���W����
	BoundingOrientedBox box_;
};