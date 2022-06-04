/**
 * @file CharaIcon.h
 * @brief 残機アイコンクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

class CharaIcon {
public:
	CharaIcon() : sprite_(DX9::SPRITE()) {}
	virtual ~CharaIcon() {}

	void LoadAssets(std::wstring file_name);
	void Render(const int life, float alpha, DirectX::XMFLOAT3 pos);

private:
	DX9::SPRITE sprite_;
};