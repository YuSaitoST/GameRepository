#include "CharaSelect.h"
#include "LobbyScene.h"
#include "_Classes/_InputManager/UseKeyChecker.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/UIPosition.h"
#include "_Classes/_StandardCalculation/StandardCalculation.h"

CharaSelect::CharaSelect() : isDecision_(false) {
	choices_		= std::make_unique<Choices>();
	ui_arrows_		= std::make_unique<SelectArrows>();
	se_decision_	= std::make_unique<SoundPlayer>();
	se_cancel_		= std::make_unique<SoundPlayer>();
	se_warning_		= std::make_unique<SoundPlayer>();
}

void CharaSelect::Initialize(int index) {
	choices_->Initialize();
	ui_arrows_->Initialize(US2D::Pos::Get().LobbyParam().ARROW_R_X[index], US2D::Pos::Get().LobbyParam().ARROW_L_X[index]);
	se_decision_->Initialize(USFN_SOUND::SE::DECISION, SOUND_TYPE::SE, 0.0f);
	se_cancel_->Initialize(USFN_SOUND::SE::CANCEL, SOUND_TYPE::SE, 0.0f);
	se_warning_->Initialize(USFN_SOUND::SE::WARNING, SOUND_TYPE::SE, 0.0f);
}

void CharaSelect::LoadAssets(DX9::SPRITE right, DX9::SPRITE left) {
	ui_arrows_->LoadAssets(right, left);
}

void CharaSelect::Update(const float deltaTime, const int index) {
	// ����ς݂̎�
	if (isDecision_) {
		// �L�����Z������
		if (INPSystem.CancelKey(index)) {
			isDecision_ = false;
			se_cancel_->PlayOneShot();
		}
		return;
	}

	choices_->Update(4, INPSystem.LeftKey(index), INPSystem.RightKey(index));
	choices_->NextSelectOn(ui_arrows_->Update(index));

	isDecision_ = INPSystem.DecisionKey(index);

	// �I�����Ă���F����
	DontDestroy->ChoseColor_[index] = choices_->SelectNum();

	// ���肵����A�F�ƃL�����̑���^�C�v��ݒ�
	if (isDecision_) {
		// �F���d�����Ă����猈��ł��Ȃ�
		if (haveSameValue(index)) {
			isDecision_ = false;
			se_warning_->PlayOneShot();
			return;
		}

		LobbyScene::ChangeModel(index, DontDestroy->ChoseColor_[index]);
		DontDestroy->charaType_[index] = CHARATYPE::TYPE_PLAYER;
		se_decision_->PlayOneShot();
	}
	else if (/*(index != 0) && */INPSystem.TabKey()) {
		InputSystem _selectType = INPSystem.GetNowInputSystem()[index];
		if (_selectType == InputSystem::COM) {
			AutoSetter(index, CHARATYPE::TYPE_COM);
			isDecision_ = true;
		}
		else if (_selectType != InputSystem::NONE) {
			AutoSetter(index, CHARATYPE::TYPE_PLAYER);
		}
		else {
			AutoSetter(index, CHARATYPE::TYPE_NONE);
		}
	}
}

void CharaSelect::Render() {
	ui_arrows_->Render(255, US2D::Pos::Get().LobbyParam().ARROW_Y);
}

/*
* @brief ��������
* @param index ���g�̔ԍ�
* @param type ������@
*/
void CharaSelect::AutoSetter(int index, CHARATYPE type) {
	SelectToAvoidDupLicates(index);
	LobbyScene::ChangeModel(index, DontDestroy->ChoseColor_[index]);
	DontDestroy->charaType_[index] = type;
	se_decision_->PlayOneShot();
	isDecision_ = true;
}

/**
* @brief �܂��I�΂�Ă��Ȃ��L������T�����I������
* @param index ���g�̔ԍ�
*/
void CharaSelect::SelectToAvoidDupLicates(int index) {
	while (haveSameValue(index)) {
		DontDestroy->ChoseColor_[index] += 1;
		StandardCalculation::ValueLoop(DontDestroy->ChoseColor_[index], 0, 4 - 1);
	}
}

/**
* @brief ���̃v���C���[���I��ł���L�����Əd�����Ă��邩�𒲂ׂ�
* @param index ���g�̔ԍ�
* @return ���̃v���C���[���I��ł���L�����Əd�����Ă���Ȃ�true
*/
bool CharaSelect::haveSameValue(int index) {
	if (DontDestroy->charaType_[index] == CHARATYPE::TYPE_NONE) {
		return false;
	}

	for (int _i = 0; _i < 4; ++_i) {
		// ������ID�������璲�ׂȂ���
		if (_i == index)
			continue;

		// �d�����Ă�����̂������true��Ԃ�
		if (DontDestroy->ChoseColor_[index] == DontDestroy->ChoseColor_[_i])
			return true;
	}

	return false;
}