#include "Choices.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_StandardCalculation/StandardCalculation.h"

Choices::Choices() : isSelected_(0), putCount_(0) {
	se_choice_ = std::make_unique<SoundPlayer>();
}

void Choices::Initialize() {
	se_choice_->Initialize(USFN_SOUND::SE::CHOICES, SOUND_TYPE::SE, 0.0f);
}

/**
 * @brief �X�V
 * @param choices �I�����̐�
 * @param low ������
 * @param high �����
*/
void Choices::Update(int choices, bool low, bool high) {
	//�A�����͂����ꂽ�瑁�����^�[������
	if (putCount_ != 0)
		return;

	isSelected_ +=
		(high) ? 1 :
		(low) ? -1 : 0;

	//�I���O�̔ԍ������[�v������
	StandardCalculation::ValueLoop(isSelected_, 0, choices - 1);

	//���͂���������SE��炷
	if (low || high) {
		se_choice_->PlayOneShot();
		putCount_ += 1;
	}
}