/**
 * @file GameField.h
 * @brief �{�҂̃t�B�[���h�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_MoviePlayer/MoviePlayer.h"

class GameField {
public:
	GameField(float sp_z);
	virtual ~GameField();
	
	void LoadAsset();
	void Update();
	void Render();

private:
	//! �w�i����
	MoviePlayer* movie_;
	
	//! ���[�v�z�[���摜
	DX9::SPRITE sp_hole_;

	//! ���W
	float sprite_z_;

	//! ���C���[�̉摜���X�g
	std::vector<DX9::SPRITE> sp_wireList_;
};