/**
 * @file MoviePlayer.h
 * @brief ����Đ��N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
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
	* @brief �Đ�
	*/
	inline void Play() { media_->Play(); }

	/**
	* @brief ��~
	*/
	inline void Stop() { media_->Stop(); }

private:
	DX9::MEDIARENDERER media_;
};