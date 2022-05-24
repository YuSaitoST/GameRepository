#include "NormalDisplay.h"
#include "DontDestroyOnLoad.h"
#include "_Classes/_FileNames/FileNames.h"
#include "_Classes/_UI/_Fade/Fade.h"

NormalDisplay::NormalDisplay() : ui_alpha_(0.0f) {
	se_decision_	= new SoundPlayer();
	time_start_		= new CountTimer(UI_FADE_STARTTIME);
	time_demo_		= new CountTimer(DEMO_PLAYBACK);
	cursor_			= new Cursor();
	mode_choices_	= new Choices();
	ui_arrows_		= new SelectArrows();
	operate_		= new OperateUI();
	blackOut_		= new BlackOut();
	text_			= nullptr;
}

NormalDisplay::~NormalDisplay() {
	delete blackOut_;
	delete operate_;
	delete ui_arrows_;
	delete mode_choices_;
	delete cursor_;
	delete time_demo_;
	delete time_start_;
	delete se_decision_;
}

void NormalDisplay::Initialize() {
	se_decision_->Initialize(USFN_SOUND::SE::DECISION_TITLE, SOUND_TYPE::SE, 2.0f);

	mode_choices_->Initialize();
	cursor_->Initialize();
	ui_arrows_->Initialize(ARROW_POS_R_X, ARROW_POS_L_X, ARROW_POS_Y);
	operate_->Initialize();
	blackOut_->Initialize(BLACKOUT_MODE::FADE_OUT);

	/*
		�I�����̃e�L�X�g��������
		���[�v�񐔂��팸���邽�߂ɁA�I�����̐����m�肵�Ă���㉺�̑I���͕��ׂċL�q
	*/
	for (int _u = 0; _u < MODE; ++_u) {
		nowText_[0][_u].Initialize(_u, Vector3(TEXT_POS_X, UI_TEXT_Y[0], -10.0f));
		nowText_[1][_u].Initialize(_u, Vector3(TEXT_POS_X, UI_TEXT_Y[1], -10.0f));
	}

	// �ŏ��ɑI����Ԃɂ���I��������
	text_ = &nowText_[0][0];
}

void NormalDisplay::LoadAssets() {
	movie_->LoadAsset(USFN_MV::TITLE_BG);
	
	cursor_->LoadAsset(USFN_SP::CURSOR);
	ui_arrows_->LoadAssets();
	operate_->LoadAsset();
	blackOut_->LoadAsset();

	/*
		�I�����Ɏg�p����摜�̃p�X��
		���[�v�񐔂��팸���邽�߂ɁA�I�����̐����m�肵�Ă���㉺�̑I���͕��ׂċL�q
	*/
	for (int _u = 0; _u < MODE; ++_u) {
		nowText_[0][_u].LoadAsset(USFN_SP::UI_TEXT[0][_u]);
		nowText_[1][_u].LoadAsset(USFN_SP::UI_TEXT[1][_u]);
	}
}

NextScene NormalDisplay::Update(const float deltaTime) {
	time_start_->Update(deltaTime);
	blackOut_->Update(SPEED_FADE[blackOut_->GetMode()] * deltaTime);

	// �^�C�g���̕\���ɍ��킹��UI���t�F�[�h�C��������
	if (time_start_->NowTime() <= 0.5f)
		FADE::In(ui_alpha_, FADE::COLORMAX, deltaTime * SPEED_ALPHA);

	// �^�C�g�����\�������܂ő���s��
	if (!time_start_->TimeOut())
		return NextScene::Continue;

	// ���艹���Ȃ�I�������L�����I����ʂ�
	if (!DontDestroy->GameMode_.isNotDecision()) {
		if (se_decision_->PlayOneShot(deltaTime) && blackOut_->isDone())
			return NextScene::LobbyScene;
		else
			return NextScene::Continue;
	}

	movie_->Update();
	cursor_->Update(CHOICES);
	time_demo_->Update(deltaTime);

	if (cursor_->SelectNum() == 0) {
		mode_choices_->Update(MODE, Press.RightKey(0), Press.LeftKey(0));
		mode_choices_->NextSelectOn(ui_arrows_->Update(0));
	}

	text_ = &nowText_[cursor_->SelectNum()][mode_choices_->SelectNum()];

	for (int _t = 0; _t < CHOICES; ++_t) {
		(_t == cursor_->SelectNum()) ?
			nowText_[_t][mode_choices_->SelectNum()].GetBigger(deltaTime) :
			nowText_[_t][mode_choices_->SelectNum()].GetSmaller(deltaTime);
	}

	/*
		����{�^������������A�I���������ڂɍ��킹���������s��
	*/
	if (Press.DecisionKey(0)) {
		se_decision_->PlayOneShot();

		if (cursor_->SelectNum() == 1)
			operate_->isPut();
		else if (!operate_->isDisplayed()) {
			blackOut_->ChangeMode(BLACKOUT_MODE::FADE_IN);
			DontDestroy->GameMode_.SelectMode((GAMEMODE)mode_choices_->SelectNum());
		}
	}

	operate_->Update(deltaTime);


	return NextScene::Continue;
}

void NormalDisplay::Render() {
	movie_->Render();
	cursor_->Render(ui_alpha_);
	ui_arrows_->Render(ui_alpha_);
	operate_->Render();
	blackOut_->Render();

	/*
		�I�����̃e�L�X�g��������
		���[�v�񐔂��팸���邽�߂ɁA�I�����̐����m�肵�Ă���㉺�̑I���͕��ׂċL�q
	*/
	nowText_[0][mode_choices_->SelectNum()].Render(ui_alpha_);
	nowText_[1][mode_choices_->SelectNum()].Render(ui_alpha_);
}

/**
 * @brief ��ʕ\����؂�ւ���ۂɕ\����Ԃ����Z�b�g����
*/
void NormalDisplay::Reset() {
	time_demo_->Reset();
}

/**
 * @brief ��ʕ\����؂�ւ��邩�̔���
 * @return �f���v���C�Đ��܂ł̎��Ԃ��o�߂�����true
*/
bool NormalDisplay::IsChange() {
	return time_demo_->TimeOut();
}