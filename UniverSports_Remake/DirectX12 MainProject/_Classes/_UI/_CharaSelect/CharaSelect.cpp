#include "CharaSelect.h"
#include "LobbyScene.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_ConstStrages/UIPosition.h"
#include "_Classes/_StandardCalculation/StandardCalculation.h"

CharaSelect::CharaSelect() {
	choices_		= std::make_unique<Choices>();
	ui_arrows_		= std::make_unique<SelectArrows>();
	se_decision_	= std::make_unique<SoundPlayer>();
	se_cancel_		= std::make_unique<SoundPlayer>();
	se_warning_		= std::make_unique<SoundPlayer>();
	isDecision_		= false;
}

void CharaSelect::Initialize(int index) {
	choices_->Initialize();
	ui_arrows_->Initialize(US2D::Pos::Get().LobbyParam().ARROW_R_X[index], US2D::Pos::Get().LobbyParam().ARROW_L_X[index], US2D::Pos::Get().LobbyParam().ARROW_Y);
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
		if (Press.CancelKey(index)) {
			isDecision_ = false;
			se_cancel_->PlayOneShot();
		}
		return;
	}

	choices_->Update(4, Press.LeftKey(index), Press.RightKey(index));
	choices_->NextSelectOn(ui_arrows_->Update(index));

	isDecision_ = Press.DecisionKey(index);

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
	else if ((index != 0) && Press.TabKey()) {
		SelectToAvoidDupLicates(index);
		LobbyScene::ChangeModel(index, DontDestroy->ChoseColor_[index]);
		DontDestroy->charaType_[index] = CHARATYPE::TYPE_COM;
		se_decision_->PlayOneShot();
		isDecision_ = true;
	}
}

void CharaSelect::Render(DX9::SPRITE& icon, DX9::SPRITE& decisions, DX9::SPRITE entry, int index) {
	ui_arrows_->Render(255);
	DX9::SpriteBatch->DrawSimple(icon.Get(), XMFLOAT3(US2D::Pos::Get().LobbyParam().PICON_X[index], US2D::Pos::Get().LobbyParam().PICON_Y, (int)US2D::Layer::LOBBY::UI_PLAYERICON));
	DX9::SpriteBatch->DrawSimple(decisions.Get(), XMFLOAT3(US2D::Pos::Get().LobbyParam().INPUT_X[index], US2D::Pos::Get().LobbyParam().INPUT_Y, (int)US2D::Layer::LOBBY::UI_DECISIONS));

	if (isDecision_)
		DX9::SpriteBatch->DrawSimple(entry.Get(), XMFLOAT3(US2D::Pos::Get().LobbyParam().ENTRY_X[index], US2D::Pos::Get().LobbyParam().ENTRY_Y, (int)US2D::Layer::LOBBY::UI_ENTRY));
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