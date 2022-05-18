/**
 * @file FieldOutCheck.h
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
	void ClampLoop(DirectX::SimpleMath::Vector2& position);
	bool IsOut(DirectX::SimpleMath::Vector2 position, float raidus);
}  //namespace FIELD