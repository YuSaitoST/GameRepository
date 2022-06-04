/**
 * @file CharaSelect.h
 * @brief �L�����I���N���X
 * @author �V���D�F
 * @date 2021/05/14
 */

#pragma once

 //------------------------------------------------------------------------------
 //	�C���N���[�h�t�@�C��
 //------------------------------------------------------------------------------
#include "_Classes/_InputClasses/UseKeyCheck.h"
#include "_Classes/_UI/_Choices/Choices.h"
#include "_Classes/_UI/_SelectArrows/SelectArrows.h"
#include "_Classes/_SoundPlayer/SoundPlayer.h"

class CharaSelect {
public:
	CharaSelect();
	virtual ~CharaSelect() {}

	CharaSelect(CharaSelect&&) = delete;
	CharaSelect& operator= (CharaSelect&&) = delete;

	CharaSelect(CharaSelect const&) = delete;
	CharaSelect& operator= (CharaSelect const&) = delete;

	void Initialize(int index);
	void LoadAssets(DX9::SPRITE right, DX9::SPRITE left);
	void Update(const float deltaTime, const int index);
	void Render(DX9::SPRITE& icon, DX9::SPRITE& decisions, DX9::SPRITE entry, int index);

	/**
	* @brief �����Ԃ�Ԃ�
	* @return ������
	*/
	inline bool IsDecision() const { return isDecision_; }

private:
	void SelectToAvoidDupLicates(int index);
	bool haveSameValue(int index);

	//! �I���N���X
	std::unique_ptr<Choices> choices_;
	
	//! ���
	std::unique_ptr<SelectArrows> ui_arrows_;
	
	//! ����SE
	std::unique_ptr<SoundPlayer> se_decision_;
	
	//! �L�����Z��SE
	std::unique_ptr<SoundPlayer> se_cancel_;
	
	//! �x��SE
	std::unique_ptr<SoundPlayer> se_warning_;
	
	//! ����t���O
	bool isDecision_;
};