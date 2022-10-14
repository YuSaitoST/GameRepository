/**
 * @file DemoDisplay.h
 * @brief �^�C�g���̃f���v���C�\���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "DisplayBase.h"
#include "_Classes/_MoviePlayer/MoviePlayer.h"

class DemoDisplay final : public DisplayBase {
public:
	DemoDisplay() { movie_ = std::make_unique<MoviePlayer>(); }
	virtual ~DemoDisplay() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual NextScene Update(const float deltaTime) override;
	virtual void Render() override;
	virtual void Reset() override;
	virtual DISPLAYMODE IsChange() override;
	virtual void ReDisplayInitialize() override;

private:
	std::unique_ptr<MoviePlayer> movie_;	//! �w�i����
};