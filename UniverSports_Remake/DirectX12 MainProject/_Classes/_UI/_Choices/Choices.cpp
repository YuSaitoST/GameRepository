#include "Choices.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_StandardCalculation/StandardCalculation.h"

Choices::Choices() {
	se_choice_ = std::make_unique<SoundPlayer>();
	isSelected = 0;
	putCount_ = 0;
}

void Choices::Initialize() {
	se_choice_->Initialize(USFN_SOUND::SE::CHOICES, SOUND_TYPE::SE, 0.0f);
}

/**
 * @brief 更新
 * @param choices 選択肢の数
 * @param low 下入力
 * @param high 上入力
*/
void Choices::Update(int choices, bool low, bool high) {
	//連続入力がされたら早期リターンする
	if (putCount_ != 0)
		return;

	isSelected +=
		(high) ? 1 :
		(low) ? -1 : 0;

	//選択外の番号をループさせる
	StandardCalculation::ValueLoop(isSelected, 0, choices - 1);

	//入力があったらSEを鳴らす
	if (low || high) {
		se_choice_->PlayOneShot();
		putCount_ += 1;
	}

}