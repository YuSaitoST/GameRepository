#include "Survivor.h"
#include "DontDestroyOnLoad.h"

/**
* @brief 残りの選手が1人かを調べる
* @return 現在残っている人数
*/
int Survivor::RemainingNumberOfPlayer() {
	int count = 0;
	count += (int)survivor_[0];
	count += (int)survivor_[1];
	count += (int)survivor_[2];
	count += (int)survivor_[3];
	return count;
}

/**
* @brief 残りのチームが1つかを調べる
* @return 現在残っているチーム数
*/
int Survivor::RemainingOfTeam() {
	// 残り人数が2人より多いまたは最後の1人なら、調べる必要がないため、早期リターンする
	const int count = RemainingNumberOfPlayer();
	if ((2 < count) || (count == 1))
		return count;

	int index = 0;
	int lastPlayersTeamID[2] = { 0,0 };

	for (int _i = 0; (_i < 4) && (index < 2); ++_i) {
		if (survivor_[_i]) {
			lastPlayersTeamID[index] = DontDestroy->TeamID[_i];
			index += 1;
		}
	}
	return (int)(lastPlayersTeamID[0] == lastPlayersTeamID[1]);
}