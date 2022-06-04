/**
 * @file MoviePlayer.h
 * @brief 動画再生クラス
 * @author 齋藤優宇
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include"Base/pch.h"
#include"Base/dxtk.h"

class MoviePlayer {
public:
	MoviePlayer() : media_(DX9::MEDIARENDERER()) {}
	virtual ~MoviePlayer() {}

	void LoadAsset(std::wstring file_name);
	void Update();
	void Render(DirectX::XMFLOAT3 pos) const;
	void Render(DirectX::XMFLOAT3 pos, const float scale) const;

	/**
	* @brief 再生
	*/
	inline void Play() { media_->Play(); }

	/**
	* @brief 停止
	*/
	inline void Stop() { media_->Stop(); }

private:
	DX9::MEDIARENDERER media_;
};