#pragma once

#include "Base/pch.h"

namespace Position {
	/**
	* @brief ��ԋ߂����W��ID��Ԃ�
	* @param positionList ���ׂ���W�̃��X�g
	* @param position �����̍��W
	* @return ��ԋ߂����W��ID
	*/
	int Nearest(std::vector<DirectX::SimpleMath::Vector2*> positionList, DirectX::SimpleMath::Vector2 position) {
		int id = -1;
		float distance = 99;
		float newDistance = 99;

		int count = positionList.size();
		for (int i = 0; i < count;++i) {
			newDistance = DirectX::SimpleMath::Vector2::Distance(position, *positionList[i]);
			if (newDistance == 0.0f) {
				continue;
			}

			if (newDistance < distance) {
				id = i;
			}
		}

		return id;
	}

}  //namespace Position