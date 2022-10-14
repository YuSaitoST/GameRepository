/**
 * @file ConfigState.h
 * @brief 設定画面の表示基底クラス
 * @author 齋藤優宇
 * @date 2021/09/17
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "Base/pch.h"
#include "Base/dxtk.h"

enum class ConfigSelector { Player, InpSystem };

// 前方宣言
class ConfigDisplay;

class ConfigState {
public:
	ConfigState() {}
	virtual ~ConfigState() {}

	virtual void Initialize() = 0;
	virtual void LoadAssets() = 0;
	virtual void Update(const float deltaTime, ConfigDisplay* conDisplay) = 0;
	virtual void Render(DX9::SPRITEFONT font) = 0;

protected:
	inline void MessageRender(DX9::SPRITEFONT font, int id) {
		DX9::SpriteBatch->DrawString(
			font.Get(),
			DirectX::XMFLOAT2(POS_AMessage_X, POS_MessageA_Y),
			DX9::Colors::Black,
			TXT_MessageA_[id].c_str()
		);
		DX9::SpriteBatch->DrawString(
			font.Get(),
			DirectX::XMFLOAT2(POS_AMessage_X, POS_MessageB_Y),
			DX9::Colors::Black,
			TXT_MessageB_[id].c_str()
		);
	}

	const int POS_AMessage_X = 100;
	const int POS_MessageA_Y = 600;
	const int POS_MessageB_Y = 650;

	const std::wstring TXT_MessageA_[2] = { L"A : タイトルに戻る",L"A : 戻る" };
	const std::wstring TXT_MessageB_[2] = { L"B : 操作方法選択",L"B : プレイヤー選択" };

};