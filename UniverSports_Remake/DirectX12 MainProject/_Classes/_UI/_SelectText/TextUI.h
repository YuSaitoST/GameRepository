/**
 * @file TextUI.h
 * @brief �I�����e�L�X�g�N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "TextBase.h"

class TextUI : public TextBase {
public:
	TextUI() {};
	virtual ~TextUI() {};

	/**
	 * @brief ������
	 * @param modeID ���[�h��ID
	 * @pos �摜�̍��W
	*/
	virtual void Initialize(int modeID, DirectX::XMFLOAT3 pos) override;

	/**
	 * @brief �t�@�C���̓ǂݍ���
	 * @param file_name �t�@�C����
	*/
	virtual void LoadAsset(std::wstring file_name) override;

	/**
	 * @brief �`��
	*/
	virtual void Render(float alpha) override;
};