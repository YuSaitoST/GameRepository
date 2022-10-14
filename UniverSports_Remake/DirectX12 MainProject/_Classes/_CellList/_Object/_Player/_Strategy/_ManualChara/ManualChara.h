/**
 * @file ManualChara.h
 * @brief �v���C���[���g�����삷��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_CellList/_Object/_Player/_Strategy/CharaStrategy.h"

class ManualChara final : public CharaStrategy {
public:
	ManualChara() {};
	virtual ~ManualChara() {};

	virtual void Initialize(int id, ObjPlayer* player) override;
	virtual void LoadAssets() override;
	virtual void Update(const float deltaTime) override;
};