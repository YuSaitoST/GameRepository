/**
 * @file InpSystemIcon.h
 * @brief キャラセレクト時のアイコンクラス
 * @author 齋藤優宇
 * @date 2021/09/23
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "_Classes/_ConstStrages/UIPosition.h"
#include "_Classes/_FileNames/FileNames.h"

class InpSystemIcon {
public:
	InpSystemIcon() {}
	virtual ~InpSystemIcon() {}

	virtual void LoadAssets() = 0;
	virtual void Render(const int playerID) = 0;

protected:
	DX9::SPRITE sprite_;
};


class EmptyIcon : public InpSystemIcon {
public:
	EmptyIcon() {}
	virtual ~EmptyIcon() {}

	virtual void LoadAssets() override {}
	virtual void Render(const int playerID) override {}
};


class COMIcon : public InpSystemIcon {
public:
	COMIcon() {}
	virtual ~COMIcon() {}

	virtual void LoadAssets() override {
		sprite_ = DX9::Sprite::CreateFromFile(DXTK->Device9, USFN_SP::INFO_COM.c_str());
	}

	virtual void Render(const int playerID) override {
		const auto _param = US2D::Pos::Get().LobbyParam();
		DX9::SpriteBatch->DrawSimple(
			sprite_.Get(), 
			DirectX::XMFLOAT3(
				_param.TEAM_COL_X[playerID], 
				_param.TEAM_COL_Y, 
				(int)US2D::Layer::LOBBY::UI_INFO_ICON
			)
		);
	}
};