/**
 * @file Field.h
 * @brief ��O�ɏo�����̃`�F�b�N
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"

namespace FIELD {
	//void Clamp(DirectX::SimpleMath::Vector2& position);
	void ClampLoop(DirectX::SimpleMath::Vector2& position);
	bool IsOut(DirectX::SimpleMath::Vector2 position, float raidus);

	//! X���W�̍ő�l
	const float SIDE_X = 32.0f;

	//! Y���W�̍ő�l
	const float SIDE_Y = 18.0f;
	
	//	//! X���W�̍ő�l
	//const float SIDE_X = 64.0f;

	////! Y���W�̍ő�l
	//const float SIDE_Y = 36.0f;

	//! X���W�̒����l
	const float CENTER_X = SIDE_X * 0.5f;
	
	//! Y���W�̒����l
	const float CENTER_Y = SIDE_Y * 0.5f;

}  //namespace FIELD