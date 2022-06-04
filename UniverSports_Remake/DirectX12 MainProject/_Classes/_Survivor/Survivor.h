/**
 * @file Survivor.h
 * @brief �����҃N���X
 * @author �V���D�F
 * @date 2021/06/04
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include <numeric>

class Survivor {
public:
	Survivor() : survivor_{ false } {}
	virtual ~Survivor() {}

	void DownSurvivor(const int id) { survivor_[id] = false; }
	void Reset() { std::fill(std::begin(survivor_), std::end(survivor_), true); }

	int RemainingNumberOfPlayer();
	int RemainingOfTeam();

private:
	bool survivor_[4];
};