/**
 * @file NearestPosition.h
 * @brief ��ԋ߂����̂𒲂ׂ鏈��
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "Base/pch.h"

namespace PosCheck {
	int GetNearestObjectID(std::vector<DirectX::SimpleMath::Vector2*> positionList, DirectX::SimpleMath::Vector2 position);

}  //namespace Position