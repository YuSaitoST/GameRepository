#include "Survivor.h"
#include "DontDestroyOnLoad.h"

/**
* @brief �c��̑I�肪1�l���𒲂ׂ�
* @return ���ݎc���Ă���l��
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
* @brief �c��̃`�[����1���𒲂ׂ�
* @return ���ݎc���Ă���`�[����
*/
int Survivor::RemainingOfTeam() {
	// �c��l����2�l��葽���܂��͍Ō��1�l�Ȃ�A���ׂ�K�v���Ȃ����߁A�������^�[������
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