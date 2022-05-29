#include "NearestPosition.h"

/**
* @brief 一番近い座標のIDを返す
* @param positionList 調べる座標のリスト
* @param position 自分の座標
* @return 一番近い座標のID
*/
int PosCheck::GetNearestObjectID(std::vector<DirectX::SimpleMath::Vector2*> positionList, DirectX::SimpleMath::Vector2 position) {
	int id = -1;
	float distance = 99;
	float newDistance = 99;

	int count = positionList.size();
	for (int i = 0; i < count; ++i) {
		newDistance = DirectX::SimpleMath::Vector2::Distance(position, *positionList[i]);
		if (newDistance == 0.0f) {
			continue;
		}

		if (newDistance < distance) {
			distance = newDistance;
			id = i;
		}
	}

	return id;
}