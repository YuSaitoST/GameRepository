/**
 * @file ConfigPLSelect.h
 * @brief �v���C���[�I���N���X
 * @author �V���D�F
 * @date 2021/09/17
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "ConfigState.h"
#include "_Classes/_UI/_Cursor/Cursor.h"

class ConfigPLSelect : public ConfigState {
public:
	ConfigPLSelect() { ui_cursor_ = std::make_unique<Cursor>(); }
	virtual ~ConfigPLSelect() {}

	virtual void Initialize() override;
	virtual void LoadAssets() override;
	virtual void Update(const float deltaTime, ConfigDisplay* conDisplay) override;
	virtual void Render(DX9::SPRITEFONT font) override;

private:
	const int CURSOR_MOVE_Y	= 85;
	const int CURSOR_POS_X	= 120;
	const int CURSOR_POS_Y	= 150;

private:
	std::unique_ptr<Cursor> ui_cursor_;
};