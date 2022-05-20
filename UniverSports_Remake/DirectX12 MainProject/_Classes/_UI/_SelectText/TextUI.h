/**
 * @file TextUI.h
 * @brief 選択肢テキストクラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include "TextBase.h"

class TextUI : public TextBase {
public:
	TextUI() {};
	virtual ~TextUI() {};

	/**
	 * @brief 初期化
	 * @param modeID モードのID
	 * @pos 画像の座標
	*/
	virtual void Initialize(int modeID, DirectX::XMFLOAT3 pos);

	/**
	 * @brief ファイルの読み込み
	 * @param file_name ファイル名
	*/
	virtual void LoadAsset(std::wstring file_name);

	/**
	 * @brief 描画
	*/
	virtual void Render(float alpha);
};